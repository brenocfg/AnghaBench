#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u_int ;
struct g_raid_volume {scalar_t__ v_strip_size; scalar_t__ v_raid_level; scalar_t__ v_raid_level_qualifier; int v_rotate_parity; int v_mdf_pdisks; int v_disks_count; struct g_raid_subdisk* v_subdisks; } ;
struct g_raid_tr_object {struct g_raid_volume* tro_volume; } ;
struct g_raid_subdisk {int dummy; } ;
struct bio_queue_head {int dummy; } ;
struct bio {char* bio_data; scalar_t__ bio_offset; int bio_length; scalar_t__ bio_error; struct g_raid_subdisk* bio_caller1; } ;
typedef  int off_t ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 scalar_t__ G_RAID_VOLUME_RL_RAID4 ; 
 scalar_t__ G_RAID_VOLUME_RL_RAID5EE ; 
 scalar_t__ G_RAID_VOLUME_RL_RAID6 ; 
 scalar_t__ G_RAID_VOLUME_RL_RAIDMDF ; 
 int MIN (scalar_t__,int) ; 
 int /*<<< orphan*/  bioq_init (struct bio_queue_head*) ; 
 int /*<<< orphan*/  bioq_insert_tail (struct bio_queue_head*,struct bio*) ; 
 struct bio* bioq_takefirst (struct bio_queue_head*) ; 
 struct bio* g_clone_bio (struct bio*) ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_raid_iodone (struct bio*,scalar_t__) ; 
 int /*<<< orphan*/  g_raid_subdisk_iostart (struct g_raid_subdisk*,struct bio*) ; 
 scalar_t__ imax (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
g_raid_tr_iostart_raid5_read(struct g_raid_tr_object *tr, struct bio *bp)
{
	struct g_raid_volume *vol;
	struct g_raid_subdisk *sd;
	struct bio_queue_head queue;
	struct bio *cbp;
	char *addr;
	off_t offset, start, length, nstripe, remain;
	int no, pno, ddisks, pdisks, protate, pleft;
	u_int strip_size, lvl, qual;

	vol = tr->tro_volume;
	addr = bp->bio_data;
	strip_size = vol->v_strip_size;
	lvl = tr->tro_volume->v_raid_level;
	qual = tr->tro_volume->v_raid_level_qualifier;
	protate = tr->tro_volume->v_rotate_parity;

	/* Stripe number. */
	nstripe = bp->bio_offset / strip_size;
	/* Start position in stripe. */
	start = bp->bio_offset % strip_size;
	/* Number of data and parity disks. */
	if (lvl == G_RAID_VOLUME_RL_RAIDMDF)
		pdisks = tr->tro_volume->v_mdf_pdisks;
	else if (lvl == G_RAID_VOLUME_RL_RAID5EE ||
	    lvl == G_RAID_VOLUME_RL_RAID6)
		pdisks = 2;
	else
		pdisks = 1;
	ddisks = vol->v_disks_count - pdisks;
	/* Parity disk number. */
	if (lvl == G_RAID_VOLUME_RL_RAID4) {
		if (qual == 0)		/* P0 */
			pno = 0;
		else			/* PN */
			pno = ddisks;
		pleft = -1;
	} else {
		pno = (nstripe / (ddisks * protate)) % vol->v_disks_count;
		pleft = protate - (nstripe / ddisks) % protate;
		if (qual >= 2) {	/* PN/Left */
			pno = ddisks - pno;
			if (pno < 0)
				pno += vol->v_disks_count;
		}
	}
	/* Data disk number. */
	no = nstripe % ddisks;
	if (lvl == G_RAID_VOLUME_RL_RAID4) {
		if (qual == 0)
			no += pdisks;
	} else if (qual & 1) {	/* Continuation/Symmetric */
		no = (pno + pdisks + no) % vol->v_disks_count;
	} else if (no >= pno)	/* Restart/Asymmetric */
		no += pdisks;
	else
		no += imax(0, pno + pdisks - vol->v_disks_count);
	/* Stripe start position in disk. */
	offset = (nstripe / ddisks) * strip_size;
	/* Length of data to operate. */
	remain = bp->bio_length;

	bioq_init(&queue);
	do {
		length = MIN(strip_size - start, remain);
		cbp = g_clone_bio(bp);
		if (cbp == NULL)
			goto failure;
		cbp->bio_offset = offset + start;
		cbp->bio_data = addr;
		cbp->bio_length = length;
		cbp->bio_caller1 = &vol->v_subdisks[no];
		bioq_insert_tail(&queue, cbp);
		no++;
		if (lvl == G_RAID_VOLUME_RL_RAID4) {
			no %= vol->v_disks_count;
			if (no == pno)
				no = (no + pdisks) % vol->v_disks_count;
		} else if (qual & 1) {	/* Continuation/Symmetric */
			no %= vol->v_disks_count;
			if (no == pno) {
				if ((--pleft) <= 0) {
					pleft += protate;
					if (qual < 2)	/* P0/Right */
						pno++;
					else		/* PN/Left */
						pno += vol->v_disks_count - 1;
					pno %= vol->v_disks_count;
				}
				no = (pno + pdisks) % vol->v_disks_count;
				offset += strip_size;
			}
		} else {		/* Restart/Asymmetric */
			if (no == pno)
				no += pdisks;
			if (no >= vol->v_disks_count) {
				no -= vol->v_disks_count;
				if ((--pleft) <= 0) {
					pleft += protate;
					if (qual < 2)	/* P0/Right */
						pno++;
					else		/* PN/Left */
						pno += vol->v_disks_count - 1;
					pno %= vol->v_disks_count;
				}
				if (no == pno)
					no += pdisks;
				else
					no += imax(0, pno + pdisks - vol->v_disks_count);
				offset += strip_size;
			}
		}
		remain -= length;
		addr += length;
		start = 0;
	} while (remain > 0);
	while ((cbp = bioq_takefirst(&queue)) != NULL) {
		sd = cbp->bio_caller1;
		cbp->bio_caller1 = NULL;
		g_raid_subdisk_iostart(sd, cbp);
	}
	return;
failure:
	while ((cbp = bioq_takefirst(&queue)) != NULL)
		g_destroy_bio(cbp);
	if (bp->bio_error == 0)
		bp->bio_error = ENOMEM;
	g_raid_iodone(bp, bp->bio_error);
}
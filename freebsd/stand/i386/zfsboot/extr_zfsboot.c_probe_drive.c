#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_t ;
struct TYPE_3__ {scalar_t__ start; scalar_t__ size; unsigned int slice; int part; int /*<<< orphan*/  unit; } ;
struct zfsdsk {int /*<<< orphan*/ * gdev; TYPE_1__ dsk; } ;
struct gpt_hdr {int hdr_lba_self; int hdr_revision; int hdr_entsz; scalar_t__ hdr_lba_table; unsigned int hdr_entries; int /*<<< orphan*/ * hdr_sig; } ;
struct gpt_ent {scalar_t__ ent_lba_start; scalar_t__ ent_lba_end; int /*<<< orphan*/  ent_type; } ;
struct dos_partition {scalar_t__ dp_start; scalar_t__ dp_size; int /*<<< orphan*/  dp_typ; } ;
typedef  int /*<<< orphan*/  hdr ;
typedef  scalar_t__ daddr_t ;
struct TYPE_4__ {char* secbuf; } ;

/* Variables and functions */
 unsigned int DEV_BSIZE ; 
 scalar_t__ DOSBBSECTOR ; 
 int DOSPARTOFF ; 
 int /*<<< orphan*/ * GPT_HDR_SIG ; 
 unsigned int NDOSPART ; 
 struct zfsdsk* copy_dsk (struct zfsdsk*) ; 
 TYPE_2__* dmadat ; 
 scalar_t__ drvread (TYPE_1__*,char*,scalar_t__,int) ; 
 scalar_t__ drvsize_ext (struct zfsdsk*) ; 
 int /*<<< orphan*/  freebsd_zfs_uuid ; 
 scalar_t__ geli_havekey (int /*<<< orphan*/ *) ; 
 scalar_t__ geli_passphrase (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* geli_taste (int /*<<< orphan*/ ,struct zfsdsk*,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  gelipw ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (struct gpt_hdr*,char*,int) ; 
 scalar_t__ vdev_probe (int /*<<< orphan*/ ,struct zfsdsk*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_read ; 
 int /*<<< orphan*/  vdev_read2 ; 

__attribute__((used)) static void
probe_drive(struct zfsdsk *zdsk)
{
#ifdef GPT
    struct gpt_hdr hdr;
    struct gpt_ent *ent;
    unsigned part, entries_per_sec;
    daddr_t slba;
#endif
#if defined(GPT) || defined(LOADER_GELI_SUPPORT)
    daddr_t elba;
#endif

    struct dos_partition *dp;
    char *sec;
    unsigned i;

#ifdef LOADER_GELI_SUPPORT
    /*
     * Taste the disk, if it is GELI encrypted, decrypt it then dig out the
     * partition table and probe each slice/partition in turn for a vdev or
     * GELI encrypted vdev.
     */
    elba = drvsize_ext(zdsk);
    if (elba > 0) {
	elba--;
    }
    zdsk->gdev = geli_taste(vdev_read, zdsk, elba, "disk%u:0:");
    if ((zdsk->gdev != NULL) && (geli_havekey(zdsk->gdev) == 0))
	    geli_passphrase(zdsk->gdev, gelipw);
#endif /* LOADER_GELI_SUPPORT */

    sec = dmadat->secbuf;
    zdsk->dsk.start = 0;

#ifdef GPT
    /*
     * First check for GPT.
     */
    if (drvread(&zdsk->dsk, sec, 1, 1)) {
	return;
    }
    memcpy(&hdr, sec, sizeof(hdr));
    if (memcmp(hdr.hdr_sig, GPT_HDR_SIG, sizeof(hdr.hdr_sig)) != 0 ||
	hdr.hdr_lba_self != 1 || hdr.hdr_revision < 0x00010000 ||
	hdr.hdr_entsz < sizeof(*ent) || DEV_BSIZE % hdr.hdr_entsz != 0) {
	goto trymbr;
    }

    /*
     * Probe all GPT partitions for the presence of ZFS pools. We
     * return the spa_t for the first we find (if requested). This
     * will have the effect of booting from the first pool on the
     * disk.
     *
     * If no vdev is found, GELI decrypting the device and try again
     */
    entries_per_sec = DEV_BSIZE / hdr.hdr_entsz;
    slba = hdr.hdr_lba_table;
    elba = slba + hdr.hdr_entries / entries_per_sec;
    while (slba < elba) {
	zdsk->dsk.start = 0;
	if (drvread(&zdsk->dsk, sec, slba, 1))
	    return;
	for (part = 0; part < entries_per_sec; part++) {
	    ent = (struct gpt_ent *)(sec + part * hdr.hdr_entsz);
	    if (memcmp(&ent->ent_type, &freebsd_zfs_uuid,
		     sizeof(uuid_t)) == 0) {
		zdsk->dsk.start = ent->ent_lba_start;
		zdsk->dsk.size = ent->ent_lba_end - ent->ent_lba_start + 1;
		zdsk->dsk.slice = part + 1;
		zdsk->dsk.part = 255;
		if (vdev_probe(vdev_read2, zdsk, NULL) == 0) {
		    /*
		     * This slice had a vdev. We need a new dsk
		     * structure now since the vdev now owns this one.
		     */
		    zdsk = copy_dsk(zdsk);
		}
#ifdef LOADER_GELI_SUPPORT
		else if ((zdsk->gdev = geli_taste(vdev_read, zdsk,
		    ent->ent_lba_end - ent->ent_lba_start, "disk%up%u:",
		    zdsk->dsk.unit, zdsk->dsk.slice)) != NULL) {
		    if (geli_havekey(zdsk->gdev) == 0 ||
			geli_passphrase(zdsk->gdev, gelipw) == 0) {
			/*
			 * This slice has GELI, check it for ZFS.
			 */
			if (vdev_probe(vdev_read2, zdsk, NULL) == 0) {
			    /*
			     * This slice had a vdev. We need a new dsk
			     * structure now since the vdev now owns this one.
			     */
			    zdsk = copy_dsk(zdsk);
			}
			break;
		    }
		}
#endif /* LOADER_GELI_SUPPORT */
	    }
	}
	slba++;
    }
    return;
trymbr:
#endif /* GPT */

    if (drvread(&zdsk->dsk, sec, DOSBBSECTOR, 1))
	return;
    dp = (void *)(sec + DOSPARTOFF);

    for (i = 0; i < NDOSPART; i++) {
	if (!dp[i].dp_typ)
	    continue;
	zdsk->dsk.start = dp[i].dp_start;
	zdsk->dsk.size = dp[i].dp_size;
	zdsk->dsk.slice = i + 1;
	if (vdev_probe(vdev_read2, zdsk, NULL) == 0) {
	    zdsk = copy_dsk(zdsk);
	}
#ifdef LOADER_GELI_SUPPORT
	else if ((zdsk->gdev = geli_taste(vdev_read, zdsk, dp[i].dp_size -
		 dp[i].dp_start, "disk%us%u:")) != NULL) {
	    if (geli_havekey(zdsk->gdev) == 0 ||
		geli_passphrase(zdsk->gdev, gelipw) == 0) {
		/*
		 * This slice has GELI, check it for ZFS.
		 */
		if (vdev_probe(vdev_read2, zdsk, NULL) == 0) {
		    /*
		     * This slice had a vdev. We need a new dsk
		     * structure now since the vdev now owns this one.
		     */
		    zdsk = copy_dsk(zdsk);
		}
		break;
	    }
	}
#endif /* LOADER_GELI_SUPPORT */
    }
}
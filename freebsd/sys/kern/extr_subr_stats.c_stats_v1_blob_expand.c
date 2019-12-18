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
struct voistat {int id; int voistatmaxid; int stats_off; int stype; int data_off; } ;
struct voi {int id; int voistatmaxid; int stats_off; int stype; int data_off; } ;
struct statsblobv1 {scalar_t__ cursz; scalar_t__ maxsz; scalar_t__ statsdata_off; scalar_t__ stats_off; struct voistat* vois; } ;

/* Variables and functions */
 struct voistat* BLOB_OFFSET (struct statsblobv1*,scalar_t__) ; 
 int EFBIG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_ZERO ; 
 int NVOIS (struct statsblobv1*) ; 
 int SB_V1_MAXSZ ; 
 int /*<<< orphan*/  memmove (struct voistat*,struct voistat*,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct voistat*,char,int) ; 
 struct statsblobv1* stats_realloc (struct statsblobv1*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
stats_v1_blob_expand(struct statsblobv1 **sbpp, int newvoibytes,
    int newvoistatbytes, int newvoistatdatabytes)
{
	struct statsblobv1 *sb;
	struct voi *tmpvoi;
	struct voistat *tmpvoistat, *voistat_array;
	int error, i, idxnewvois, idxnewvoistats, nbytes, nvoistats;

	KASSERT(newvoibytes % sizeof(struct voi) == 0,
	    ("Bad newvoibytes %d", newvoibytes));
	KASSERT(newvoistatbytes % sizeof(struct voistat) == 0,
	    ("Bad newvoistatbytes %d", newvoistatbytes));

	error = ((newvoibytes % sizeof(struct voi) == 0) &&
	    (newvoistatbytes % sizeof(struct voistat) == 0)) ? 0 : EINVAL;
	sb = *sbpp;
	nbytes = newvoibytes + newvoistatbytes + newvoistatdatabytes;

	/*
	 * XXXLAS: Required until we gain support for flags which alter the
	 * units of size/offset fields in key structs.
	 */
	if (!error && ((((int)sb->cursz) + nbytes) > SB_V1_MAXSZ))
		error = EFBIG;

	if (!error && (sb->cursz + nbytes > sb->maxsz)) {
		/* Need to expand our blob. */
		sb = stats_realloc(sb, sb->maxsz, sb->cursz + nbytes, M_ZERO);
		if (sb != NULL) {
			sb->maxsz = sb->cursz + nbytes;
			*sbpp = sb;
		} else
		    error = ENOMEM;
	}

	if (!error) {
		/*
		 * Shuffle memory within the expanded blob working from the end
		 * backwards, leaving gaps for the new voistat and voistatdata
		 * structs at the beginning of their respective blob regions,
		 * and for the new voi structs at the end of their blob region.
		 */
		memmove(BLOB_OFFSET(sb, sb->statsdata_off + nbytes),
		    BLOB_OFFSET(sb, sb->statsdata_off),
		    sb->cursz - sb->statsdata_off);
		memmove(BLOB_OFFSET(sb, sb->stats_off + newvoibytes +
		    newvoistatbytes), BLOB_OFFSET(sb, sb->stats_off),
		    sb->statsdata_off - sb->stats_off);

		/* First index of new voi/voistat structs to be initialised. */
		idxnewvois = NVOIS(sb);
		idxnewvoistats = (newvoistatbytes / sizeof(struct voistat)) - 1;

		/* Update housekeeping variables and offsets. */
		sb->cursz += nbytes;
		sb->stats_off += newvoibytes;
		sb->statsdata_off += newvoibytes + newvoistatbytes;

		/* XXXLAS: Zeroing not strictly needed but aids debugging. */
		memset(&sb->vois[idxnewvois], '\0', newvoibytes);
		memset(BLOB_OFFSET(sb, sb->stats_off), '\0',
		    newvoistatbytes);
		memset(BLOB_OFFSET(sb, sb->statsdata_off), '\0',
		    newvoistatdatabytes);

		/* Initialise new voi array members and update offsets. */
		for (i = 0; i < NVOIS(sb); i++) {
			tmpvoi = &sb->vois[i];
			if (i >= idxnewvois) {
				tmpvoi->id = tmpvoi->voistatmaxid = -1;
			} else if (tmpvoi->id > -1) {
				tmpvoi->stats_off += newvoibytes +
				    newvoistatbytes;
			}
		}

		/* Initialise new voistat array members and update offsets. */
		nvoistats = (sb->statsdata_off - sb->stats_off) /
		    sizeof(struct voistat);
		voistat_array = BLOB_OFFSET(sb, sb->stats_off);
		for (i = 0; i < nvoistats; i++) {
			tmpvoistat = &voistat_array[i];
			if (i <= idxnewvoistats) {
				tmpvoistat->stype = -1;
			} else if (tmpvoistat->stype > -1) {
				tmpvoistat->data_off += nbytes;
			}
		}
	}

	return (error);
}
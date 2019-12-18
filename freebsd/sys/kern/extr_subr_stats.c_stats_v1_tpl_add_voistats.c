#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct voistatspec {int stype; scalar_t__ vs_dtype; int vsdsz; int /*<<< orphan*/ * iv; scalar_t__ flags; } ;
struct voistatdata_voistate {int dummy; } ;
struct voistatdata_numeric {int dummy; } ;
struct voistat {int stype; int dtype; int dsz; scalar_t__ data_off; scalar_t__ flags; } ;
struct voi_meta {int /*<<< orphan*/ * name; } ;
struct voi {int id; int voistatmaxid; int dtype; int flags; scalar_t__ stats_off; } ;
struct statsblobv1 {scalar_t__ statsdata_off; scalar_t__ stats_off; struct voi* vois; } ;
struct statsblob {int dummy; } ;
struct metablob {struct voi_meta* voi_meta; } ;
typedef  size_t int32_t ;
typedef  enum vsd_dtype { ____Placeholder_vsd_dtype } vsd_dtype ;
struct TYPE_3__ {struct statsblob* sb; struct metablob* mb; } ;

/* Variables and functions */
 struct voistat* BLOB_OFFSET (struct statsblobv1*,scalar_t__) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_ZERO ; 
 int NVOIS (struct statsblobv1*) ; 
 int SB_VOI_RELUPDATE ; 
 int /*<<< orphan*/  TPL_LIST_WLOCK () ; 
 int /*<<< orphan*/  TPL_LIST_WUNLOCK () ; 
 int VOI_REQSTATE ; 
 int VSD_DTYPE_VOISTATE ; 
 int VSD_NUM_DTYPES ; 
 int VS_NUM_STYPES ; 
 int VS_STYPE_VOISTATE ; 
 int /*<<< orphan*/  memcpy (struct voistat*,int /*<<< orphan*/ *,int) ; 
 int ntpl ; 
 struct voi_meta* stats_realloc (struct voi_meta*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stats_strdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stats_tpl_update_hash (TYPE_1__*) ; 
 int stats_v1_blob_expand (struct statsblobv1**,int,int,int) ; 
 TYPE_1__** tpllist ; 

int
stats_v1_tpl_add_voistats(uint32_t tpl_id, int32_t voi_id, const char *voi_name,
    enum vsd_dtype voi_dtype, uint32_t nvss, struct voistatspec *vss,
    uint32_t flags)
{
	struct voi *voi;
	struct voistat *tmpstat;
	struct statsblobv1 *tpl_sb;
	struct metablob *tpl_mb;
	int error, i, newstatdataidx, newvoibytes, newvoistatbytes,
	    newvoistatdatabytes, newvoistatmaxid;
	uint32_t nbytes;

	if (voi_id < 0 || voi_dtype == 0 || voi_dtype >= VSD_NUM_DTYPES ||
	    nvss == 0 || vss == NULL)
		return (EINVAL);

	error = nbytes = newvoibytes = newvoistatbytes =
	    newvoistatdatabytes = 0;
	newvoistatmaxid = -1;

	/* Calculate the number of bytes required for the new voistats. */
	for (i = nvss - 1; i >= 0; i--) {
		if (vss[i].stype == 0 || vss[i].stype >= VS_NUM_STYPES ||
		    vss[i].vs_dtype == 0 || vss[i].vs_dtype >= VSD_NUM_DTYPES ||
		    vss[i].iv == NULL || vss[i].vsdsz == 0)
			return (EINVAL);
		if ((int)vss[i].stype > newvoistatmaxid)
			newvoistatmaxid = vss[i].stype;
		newvoistatdatabytes += vss[i].vsdsz;
	}

	if (flags & SB_VOI_RELUPDATE) {
		/* XXXLAS: VOI state bytes may need to vary based on stat types. */
		newvoistatdatabytes += sizeof(struct voistatdata_voistate);
	}
	nbytes += newvoistatdatabytes;

	TPL_LIST_WLOCK();
	if (tpl_id < ntpl) {
		tpl_sb = (struct statsblobv1 *)tpllist[tpl_id]->sb;
		tpl_mb = tpllist[tpl_id]->mb;

		if (voi_id >= NVOIS(tpl_sb) || tpl_sb->vois[voi_id].id == -1) {
			/* Adding a new VOI and associated stats. */
			if (voi_id >= NVOIS(tpl_sb)) {
				/* We need to grow the tpl_sb->vois array. */
				newvoibytes = (voi_id - (NVOIS(tpl_sb) - 1)) *
				    sizeof(struct voi);
				nbytes += newvoibytes;
			}
			newvoistatbytes =
			    (newvoistatmaxid + 1) * sizeof(struct voistat);
		} else {
			/* Adding stats to an existing VOI. */
			if (newvoistatmaxid >
			    tpl_sb->vois[voi_id].voistatmaxid) {
				newvoistatbytes = (newvoistatmaxid -
				    tpl_sb->vois[voi_id].voistatmaxid) *
				    sizeof(struct voistat);
			}
			/* XXXLAS: KPI does not yet support expanding VOIs. */
			error = EOPNOTSUPP;
		}
		nbytes += newvoistatbytes;

		if (!error && newvoibytes > 0) {
			struct voi_meta *voi_meta = tpl_mb->voi_meta;

			voi_meta = stats_realloc(voi_meta, voi_meta == NULL ?
			    0 : NVOIS(tpl_sb) * sizeof(struct voi_meta),
			    (1 + voi_id) * sizeof(struct voi_meta),
			    M_ZERO);

			if (voi_meta == NULL)
				error = ENOMEM;
			else
				tpl_mb->voi_meta = voi_meta;
		}

		if (!error) {
			/* NB: Resizing can change where tpl_sb points. */
			error = stats_v1_blob_expand(&tpl_sb, newvoibytes,
			    newvoistatbytes, newvoistatdatabytes);
		}

		if (!error) {
			tpl_mb->voi_meta[voi_id].name = stats_strdup(voi_name,
			    0);
			if (tpl_mb->voi_meta[voi_id].name == NULL)
				error = ENOMEM;
		}

		if (!error) {
			/* Update the template list with the resized pointer. */
			tpllist[tpl_id]->sb = (struct statsblob *)tpl_sb;

			/* Update the template. */
			voi = &tpl_sb->vois[voi_id];

			if (voi->id < 0) {
				/* VOI is new and needs to be initialised. */
				voi->id = voi_id;
				voi->dtype = voi_dtype;
				voi->stats_off = tpl_sb->stats_off;
				if (flags & SB_VOI_RELUPDATE)
					voi->flags |= VOI_REQSTATE;
			} else {
				/*
				 * XXXLAS: When this else block is written, the
				 * "KPI does not yet support expanding VOIs"
				 * error earlier in this function can be
				 * removed. What is required here is to shuffle
				 * the voistat array such that the new stats for
				 * the voi are contiguous, which will displace
				 * stats for other vois that reside after the
				 * voi being updated. The other vois then need
				 * to have their stats_off adjusted post
				 * shuffle.
				 */
			}

			voi->voistatmaxid = newvoistatmaxid;
			newstatdataidx = 0;

			if (voi->flags & VOI_REQSTATE) {
				/* Initialise the voistate stat in slot 0. */
				tmpstat = BLOB_OFFSET(tpl_sb, voi->stats_off);
				tmpstat->stype = VS_STYPE_VOISTATE;
				tmpstat->flags = 0;
				tmpstat->dtype = VSD_DTYPE_VOISTATE;
				newstatdataidx = tmpstat->dsz =
				    sizeof(struct voistatdata_numeric);
				tmpstat->data_off = tpl_sb->statsdata_off;
			}

			for (i = 0; (uint32_t)i < nvss; i++) {
				tmpstat = BLOB_OFFSET(tpl_sb, voi->stats_off +
				    (vss[i].stype * sizeof(struct voistat)));
				KASSERT(tmpstat->stype < 0, ("voistat %p "
				    "already initialised", tmpstat));
				tmpstat->stype = vss[i].stype;
				tmpstat->flags = vss[i].flags;
				tmpstat->dtype = vss[i].vs_dtype;
				tmpstat->dsz = vss[i].vsdsz;
				tmpstat->data_off = tpl_sb->statsdata_off +
				    newstatdataidx;
				memcpy(BLOB_OFFSET(tpl_sb, tmpstat->data_off),
				    vss[i].iv, vss[i].vsdsz);
				newstatdataidx += vss[i].vsdsz;
			}

			/* Update the template version hash. */
			stats_tpl_update_hash(tpllist[tpl_id]);
			/* XXXLAS: Confirm tpl name/hash pair remains unique. */
		}
	} else
		error = EINVAL;
	TPL_LIST_WUNLOCK();

	return (error);
}
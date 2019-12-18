#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_22__ {int /*<<< orphan*/  uq64; int /*<<< orphan*/  sq64; } ;
struct TYPE_20__ {int /*<<< orphan*/  uq32; int /*<<< orphan*/  sq32; } ;
struct TYPE_18__ {int /*<<< orphan*/  ulong; int /*<<< orphan*/  slong; } ;
struct TYPE_16__ {int /*<<< orphan*/  u64; int /*<<< orphan*/  s64; } ;
struct TYPE_14__ {int /*<<< orphan*/  u32; int /*<<< orphan*/  s32; } ;
struct voistatdata {TYPE_7__ q64; TYPE_5__ q32; TYPE_3__ intlong; TYPE_1__ int64; TYPE_11__ int32; } ;
struct voistat {int stype; int /*<<< orphan*/  data_off; } ;
struct voi {int dtype; scalar_t__ id; int flags; int voistatmaxid; int /*<<< orphan*/  stats_off; } ;
struct statsblobv1 {scalar_t__ abi; struct voi* vois; } ;
typedef  size_t int32_t ;
typedef  enum vsd_dtype { ____Placeholder_vsd_dtype } vsd_dtype ;
struct TYPE_24__ {int /*<<< orphan*/  u32; int /*<<< orphan*/  s32; } ;
struct TYPE_23__ {int /*<<< orphan*/  uq64; int /*<<< orphan*/  sq64; } ;
struct TYPE_21__ {int /*<<< orphan*/  uq32; int /*<<< orphan*/  sq32; } ;
struct TYPE_19__ {int /*<<< orphan*/  ulong; int /*<<< orphan*/  slong; } ;
struct TYPE_17__ {int /*<<< orphan*/  u64; int /*<<< orphan*/  s64; } ;
struct TYPE_13__ {TYPE_8__ q64; TYPE_6__ q32; TYPE_4__ intlong; TYPE_2__ int64; TYPE_9__ int32; } ;
struct TYPE_15__ {TYPE_10__ prev; } ;

/* Variables and functions */
 void* BLOB_OFFSET (struct statsblobv1*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 size_t NVOIS (struct statsblobv1*) ; 
 int Q_QADDQ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int Q_QCPYVALQ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SB_VOI_RELUPDATE ; 
 scalar_t__ STATS_ABI_V1 ; 
 int VOI_REQSTATE ; 
 TYPE_12__* VSD (int /*<<< orphan*/ ,void*) ; 
#define  VSD_DTYPE_INT_S32 142 
#define  VSD_DTYPE_INT_S64 141 
#define  VSD_DTYPE_INT_SLONG 140 
#define  VSD_DTYPE_INT_U32 139 
#define  VSD_DTYPE_INT_U64 138 
#define  VSD_DTYPE_INT_ULONG 137 
#define  VSD_DTYPE_Q_S32 136 
#define  VSD_DTYPE_Q_S64 135 
#define  VSD_DTYPE_Q_U32 134 
#define  VSD_DTYPE_Q_U64 133 
 int VSD_NUM_DTYPES ; 
 int /*<<< orphan*/  VS_INCERRS (struct voistat*) ; 
#define  VS_STYPE_HIST 132 
#define  VS_STYPE_MAX 131 
#define  VS_STYPE_MIN 130 
#define  VS_STYPE_SUM 129 
#define  VS_STYPE_TDGST 128 
 int stats_v1_voi_update_hist (int,struct voistatdata*,struct voistat*,void*) ; 
 int stats_v1_voi_update_max (int,struct voistatdata*,struct voistat*,void*) ; 
 int stats_v1_voi_update_min (int,struct voistatdata*,struct voistat*,void*) ; 
 int stats_v1_voi_update_sum (int,struct voistatdata*,struct voistat*,void*) ; 
 int stats_v1_voi_update_tdgst (int,struct voistatdata*,struct voistat*,void*) ; 
 int /*<<< orphan*/  voistate ; 

int
stats_v1_voi_update(struct statsblobv1 *sb, int32_t voi_id,
    enum vsd_dtype voi_dtype, struct voistatdata *voival, uint32_t flags)
{
	struct voi *v;
	struct voistat *vs;
	void *statevsd, *vsd;
	int error, i, tmperr;

	error = 0;

	if (sb == NULL || sb->abi != STATS_ABI_V1 || voi_id >= NVOIS(sb) ||
	    voi_dtype == 0 || voi_dtype >= VSD_NUM_DTYPES || voival == NULL)
		return (EINVAL);
	v = &sb->vois[voi_id];
	if (voi_dtype != v->dtype || v->id < 0 ||
	    ((flags & SB_VOI_RELUPDATE) && !(v->flags & VOI_REQSTATE)))
		return (EINVAL);

	vs = BLOB_OFFSET(sb, v->stats_off);
	if (v->flags & VOI_REQSTATE)
		statevsd = BLOB_OFFSET(sb, vs->data_off);
	else
		statevsd = NULL;

	if (flags & SB_VOI_RELUPDATE) {
		switch (voi_dtype) {
		case VSD_DTYPE_INT_S32:
			voival->int32.s32 +=
			    VSD(voistate, statevsd)->prev.int32.s32;
			break;
		case VSD_DTYPE_INT_U32:
			voival->int32.u32 +=
			    VSD(voistate, statevsd)->prev.int32.u32;
			break;
		case VSD_DTYPE_INT_S64:
			voival->int64.s64 +=
			    VSD(voistate, statevsd)->prev.int64.s64;
			break;
		case VSD_DTYPE_INT_U64:
			voival->int64.u64 +=
			    VSD(voistate, statevsd)->prev.int64.u64;
			break;
		case VSD_DTYPE_INT_SLONG:
			voival->intlong.slong +=
			    VSD(voistate, statevsd)->prev.intlong.slong;
			break;
		case VSD_DTYPE_INT_ULONG:
			voival->intlong.ulong +=
			    VSD(voistate, statevsd)->prev.intlong.ulong;
			break;
		case VSD_DTYPE_Q_S32:
			error = Q_QADDQ(&voival->q32.sq32,
			    VSD(voistate, statevsd)->prev.q32.sq32);
			break;
		case VSD_DTYPE_Q_U32:
			error = Q_QADDQ(&voival->q32.uq32,
			    VSD(voistate, statevsd)->prev.q32.uq32);
			break;
		case VSD_DTYPE_Q_S64:
			error = Q_QADDQ(&voival->q64.sq64,
			    VSD(voistate, statevsd)->prev.q64.sq64);
			break;
		case VSD_DTYPE_Q_U64:
			error = Q_QADDQ(&voival->q64.uq64,
			    VSD(voistate, statevsd)->prev.q64.uq64);
			break;
		default:
			KASSERT(0, ("Unknown VOI data type %d", voi_dtype));
			break;
		}
	}

	if (error)
		return (error);

	for (i = v->voistatmaxid; i > 0; i--) {
		vs = &((struct voistat *)BLOB_OFFSET(sb, v->stats_off))[i];
		if (vs->stype < 0)
			continue;

		vsd = BLOB_OFFSET(sb, vs->data_off);

		switch (vs->stype) {
		case VS_STYPE_MAX:
			tmperr = stats_v1_voi_update_max(voi_dtype, voival,
			    vs, vsd);
			break;
		case VS_STYPE_MIN:
			tmperr = stats_v1_voi_update_min(voi_dtype, voival,
			    vs, vsd);
			break;
		case VS_STYPE_SUM:
			tmperr = stats_v1_voi_update_sum(voi_dtype, voival,
			    vs, vsd);
			break;
		case VS_STYPE_HIST:
			tmperr = stats_v1_voi_update_hist(voi_dtype, voival,
			    vs, vsd);
			break;
		case VS_STYPE_TDGST:
			tmperr = stats_v1_voi_update_tdgst(voi_dtype, voival,
			    vs, vsd);
			break;
		default:
			KASSERT(0, ("Unknown VOI stat type %d", vs->stype));
			break;
		}

		if (tmperr) {
			error = tmperr;
			VS_INCERRS(vs);
		}
	}

	if (statevsd) {
		switch (voi_dtype) {
		case VSD_DTYPE_INT_S32:
			VSD(voistate, statevsd)->prev.int32.s32 =
			    voival->int32.s32;
			break;
		case VSD_DTYPE_INT_U32:
			VSD(voistate, statevsd)->prev.int32.u32 =
			    voival->int32.u32;
			break;
		case VSD_DTYPE_INT_S64:
			VSD(voistate, statevsd)->prev.int64.s64 =
			    voival->int64.s64;
			break;
		case VSD_DTYPE_INT_U64:
			VSD(voistate, statevsd)->prev.int64.u64 =
			    voival->int64.u64;
			break;
		case VSD_DTYPE_INT_SLONG:
			VSD(voistate, statevsd)->prev.intlong.slong =
			    voival->intlong.slong;
			break;
		case VSD_DTYPE_INT_ULONG:
			VSD(voistate, statevsd)->prev.intlong.ulong =
			    voival->intlong.ulong;
			break;
		case VSD_DTYPE_Q_S32:
			error = Q_QCPYVALQ(
			    &VSD(voistate, statevsd)->prev.q32.sq32,
			    voival->q32.sq32);
			break;
		case VSD_DTYPE_Q_U32:
			error = Q_QCPYVALQ(
			    &VSD(voistate, statevsd)->prev.q32.uq32,
			    voival->q32.uq32);
			break;
		case VSD_DTYPE_Q_S64:
			error = Q_QCPYVALQ(
			    &VSD(voistate, statevsd)->prev.q64.sq64,
			    voival->q64.sq64);
			break;
		case VSD_DTYPE_Q_U64:
			error = Q_QCPYVALQ(
			    &VSD(voistate, statevsd)->prev.q64.uq64,
			    voival->q64.uq64);
			break;
		default:
			KASSERT(0, ("Unknown VOI data type %d", voi_dtype));
			break;
		}
	}

	return (error);
}
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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_14__ {int /*<<< orphan*/  uq64; int /*<<< orphan*/  sq64; } ;
struct TYPE_24__ {int /*<<< orphan*/  uq32; int /*<<< orphan*/  sq32; } ;
struct TYPE_22__ {int /*<<< orphan*/  ulong; int /*<<< orphan*/  slong; } ;
struct TYPE_20__ {int /*<<< orphan*/  u64; int /*<<< orphan*/  s64; } ;
struct TYPE_18__ {int /*<<< orphan*/  u32; int /*<<< orphan*/  s32; } ;
struct voistatdata_numeric {TYPE_11__ q64; TYPE_9__ q32; TYPE_7__ intlong; TYPE_5__ int64; TYPE_3__ int32; } ;
struct voistatdata_hist {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  uq64; int /*<<< orphan*/  sq64; } ;
struct TYPE_23__ {int /*<<< orphan*/  uq32; int /*<<< orphan*/  sq32; } ;
struct TYPE_21__ {int /*<<< orphan*/  ulong; int /*<<< orphan*/  slong; } ;
struct TYPE_19__ {int /*<<< orphan*/  u64; int /*<<< orphan*/  s64; } ;
struct TYPE_17__ {int /*<<< orphan*/  u32; int /*<<< orphan*/  s32; } ;
struct voistatdata {TYPE_10__ q64; TYPE_8__ q32; TYPE_6__ intlong; TYPE_4__ int64; TYPE_2__ int32; } ;
struct voistat {int dtype; int /*<<< orphan*/  flags; int /*<<< orphan*/  dsz; } ;
typedef  enum vsd_dtype { ____Placeholder_vsd_dtype } vsd_dtype ;
struct TYPE_16__ {int cnt; struct voistatdata_numeric val; struct voistatdata_numeric ub; struct voistatdata_numeric lb; } ;
struct TYPE_15__ {int oob; TYPE_1__* bkts; } ;

/* Variables and functions */
 int EINVAL ; 
 int HIST_VSDSZ2NBKTS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_QEQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_QGEQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_QLTQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_12__* VSD (int /*<<< orphan*/ ,struct voistatdata_hist*) ; 
#define  VSD_DTYPE_CRHIST32 143 
#define  VSD_DTYPE_CRHIST64 142 
#define  VSD_DTYPE_DRHIST32 141 
#define  VSD_DTYPE_DRHIST64 140 
#define  VSD_DTYPE_DVHIST32 139 
#define  VSD_DTYPE_DVHIST64 138 
#define  VSD_DTYPE_INT_S32 137 
#define  VSD_DTYPE_INT_S64 136 
#define  VSD_DTYPE_INT_SLONG 135 
#define  VSD_DTYPE_INT_U32 134 
#define  VSD_DTYPE_INT_U64 133 
#define  VSD_DTYPE_INT_ULONG 132 
#define  VSD_DTYPE_Q_S32 131 
#define  VSD_DTYPE_Q_S64 130 
#define  VSD_DTYPE_Q_U32 129 
#define  VSD_DTYPE_Q_U64 128 
 int /*<<< orphan*/  VS_VSDVALID ; 
 int /*<<< orphan*/  crhist32 ; 
 int /*<<< orphan*/  crhist64 ; 
 int /*<<< orphan*/  drhist32 ; 
 int /*<<< orphan*/  drhist64 ; 
 int /*<<< orphan*/  dvhist32 ; 
 int /*<<< orphan*/  dvhist64 ; 

__attribute__((used)) static inline int
stats_v1_voi_update_hist(enum vsd_dtype voi_dtype, struct voistatdata *voival,
    struct voistat *vs, struct voistatdata_hist *hist)
{
	struct voistatdata_numeric *bkt_lb, *bkt_ub;
	uint64_t *oob64, *cnt64;
	uint32_t *oob32, *cnt32;
	int error, i, found, is32bit, has_ub, eq_only;

	error = 0;

	switch (vs->dtype) {
	case VSD_DTYPE_CRHIST32:
		i = HIST_VSDSZ2NBKTS(crhist32, vs->dsz);
		is32bit = 1;
		has_ub = eq_only = 0;
		oob32 = &VSD(crhist32, hist)->oob;
		break;
	case VSD_DTYPE_DRHIST32:
		i = HIST_VSDSZ2NBKTS(drhist32, vs->dsz);
		is32bit = has_ub = 1;
		eq_only = 0;
		oob32 = &VSD(drhist32, hist)->oob;
		break;
	case VSD_DTYPE_DVHIST32:
		i = HIST_VSDSZ2NBKTS(dvhist32, vs->dsz);
		is32bit = eq_only = 1;
		has_ub = 0;
		oob32 = &VSD(dvhist32, hist)->oob;
		break;
	case VSD_DTYPE_CRHIST64:
		i = HIST_VSDSZ2NBKTS(crhist64, vs->dsz);
		is32bit = has_ub = eq_only = 0;
		oob64 = &VSD(crhist64, hist)->oob;
		break;
	case VSD_DTYPE_DRHIST64:
		i = HIST_VSDSZ2NBKTS(drhist64, vs->dsz);
		is32bit = eq_only = 0;
		has_ub = 1;
		oob64 = &VSD(drhist64, hist)->oob;
		break;
	case VSD_DTYPE_DVHIST64:
		i = HIST_VSDSZ2NBKTS(dvhist64, vs->dsz);
		is32bit = has_ub = 0;
		eq_only = 1;
		oob64 = &VSD(dvhist64, hist)->oob;
		break;
	default:
		return (EINVAL);
	}
	i--; /* Adjust for 0-based array index. */

	/* XXXLAS: Should probably use a better bucket search algorithm. ARB? */
	for (found = 0; i >= 0 && !found; i--) {
		switch (vs->dtype) {
		case VSD_DTYPE_CRHIST32:
			bkt_lb = &VSD(crhist32, hist)->bkts[i].lb;
			cnt32 = &VSD(crhist32, hist)->bkts[i].cnt;
			break;
		case VSD_DTYPE_DRHIST32:
			bkt_lb = &VSD(drhist32, hist)->bkts[i].lb;
			bkt_ub = &VSD(drhist32, hist)->bkts[i].ub;
			cnt32 = &VSD(drhist32, hist)->bkts[i].cnt;
			break;
		case VSD_DTYPE_DVHIST32:
			bkt_lb = &VSD(dvhist32, hist)->bkts[i].val;
			cnt32 = &VSD(dvhist32, hist)->bkts[i].cnt;
			break;
		case VSD_DTYPE_CRHIST64:
			bkt_lb = &VSD(crhist64, hist)->bkts[i].lb;
			cnt64 = &VSD(crhist64, hist)->bkts[i].cnt;
			break;
		case VSD_DTYPE_DRHIST64:
			bkt_lb = &VSD(drhist64, hist)->bkts[i].lb;
			bkt_ub = &VSD(drhist64, hist)->bkts[i].ub;
			cnt64 = &VSD(drhist64, hist)->bkts[i].cnt;
			break;
		case VSD_DTYPE_DVHIST64:
			bkt_lb = &VSD(dvhist64, hist)->bkts[i].val;
			cnt64 = &VSD(dvhist64, hist)->bkts[i].cnt;
			break;
		default:
			return (EINVAL);
		}

		switch (voi_dtype) {
		case VSD_DTYPE_INT_S32:
			if (voival->int32.s32 >= bkt_lb->int32.s32) {
				if ((eq_only && voival->int32.s32 ==
				    bkt_lb->int32.s32) ||
				    (!eq_only && (!has_ub ||
				    voival->int32.s32 < bkt_ub->int32.s32)))
					found = 1;
			}
			break;
		case VSD_DTYPE_INT_U32:
			if (voival->int32.u32 >= bkt_lb->int32.u32) {
				if ((eq_only && voival->int32.u32 ==
				    bkt_lb->int32.u32) ||
				    (!eq_only && (!has_ub ||
				    voival->int32.u32 < bkt_ub->int32.u32)))
					found = 1;
			}
			break;
		case VSD_DTYPE_INT_S64:
			if (voival->int64.s64 >= bkt_lb->int64.s64)
				if ((eq_only && voival->int64.s64 ==
				    bkt_lb->int64.s64) ||
				    (!eq_only && (!has_ub ||
				    voival->int64.s64 < bkt_ub->int64.s64)))
					found = 1;
			break;
		case VSD_DTYPE_INT_U64:
			if (voival->int64.u64 >= bkt_lb->int64.u64)
				if ((eq_only && voival->int64.u64 ==
				    bkt_lb->int64.u64) ||
				    (!eq_only && (!has_ub ||
				    voival->int64.u64 < bkt_ub->int64.u64)))
					found = 1;
			break;
		case VSD_DTYPE_INT_SLONG:
			if (voival->intlong.slong >= bkt_lb->intlong.slong)
				if ((eq_only && voival->intlong.slong ==
				    bkt_lb->intlong.slong) ||
				    (!eq_only && (!has_ub ||
				    voival->intlong.slong <
				    bkt_ub->intlong.slong)))
					found = 1;
			break;
		case VSD_DTYPE_INT_ULONG:
			if (voival->intlong.ulong >= bkt_lb->intlong.ulong)
				if ((eq_only && voival->intlong.ulong ==
				    bkt_lb->intlong.ulong) ||
				    (!eq_only && (!has_ub ||
				    voival->intlong.ulong <
				    bkt_ub->intlong.ulong)))
					found = 1;
			break;
		case VSD_DTYPE_Q_S32:
			if (Q_QGEQ(voival->q32.sq32, bkt_lb->q32.sq32))
				if ((eq_only && Q_QEQ(voival->q32.sq32,
				    bkt_lb->q32.sq32)) ||
				    (!eq_only && (!has_ub ||
				    Q_QLTQ(voival->q32.sq32,
				    bkt_ub->q32.sq32))))
					found = 1;
			break;
		case VSD_DTYPE_Q_U32:
			if (Q_QGEQ(voival->q32.uq32, bkt_lb->q32.uq32))
				if ((eq_only && Q_QEQ(voival->q32.uq32,
				    bkt_lb->q32.uq32)) ||
				    (!eq_only && (!has_ub ||
				    Q_QLTQ(voival->q32.uq32,
				    bkt_ub->q32.uq32))))
					found = 1;
			break;
		case VSD_DTYPE_Q_S64:
			if (Q_QGEQ(voival->q64.sq64, bkt_lb->q64.sq64))
				if ((eq_only && Q_QEQ(voival->q64.sq64,
				    bkt_lb->q64.sq64)) ||
				    (!eq_only && (!has_ub ||
				    Q_QLTQ(voival->q64.sq64,
				    bkt_ub->q64.sq64))))
					found = 1;
			break;
		case VSD_DTYPE_Q_U64:
			if (Q_QGEQ(voival->q64.uq64, bkt_lb->q64.uq64))
				if ((eq_only && Q_QEQ(voival->q64.uq64,
				    bkt_lb->q64.uq64)) ||
				    (!eq_only && (!has_ub ||
				    Q_QLTQ(voival->q64.uq64,
				    bkt_ub->q64.uq64))))
					found = 1;
			break;
		default:
			break;
		}
	}

	if (found) {
		if (is32bit)
			*cnt32 += 1;
		else
			*cnt64 += 1;
	} else {
		if (is32bit)
			*oob32 += 1;
		else
			*oob64 += 1;
	}

	vs->flags |= VS_VSDVALID;
	return (error);
}
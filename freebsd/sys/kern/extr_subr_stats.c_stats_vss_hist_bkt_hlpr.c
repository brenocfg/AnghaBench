#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  u64q_t ;
typedef  int /*<<< orphan*/  u32q_t ;
struct TYPE_16__ {TYPE_4__* bkts; } ;
struct TYPE_14__ {scalar_t__ linstepdiv; int /*<<< orphan*/  stepbase; } ;
struct TYPE_13__ {int /*<<< orphan*/  stepexp; int /*<<< orphan*/  stepbase; } ;
struct TYPE_12__ {scalar_t__ stepinc; } ;
struct vss_hist_hlpr_info {int scheme; int voi_dtype; TYPE_5__ usr; TYPE_3__ linexp; TYPE_2__ exp; TYPE_1__ lin; } ;
struct TYPE_11__ {int /*<<< orphan*/  uq64; int /*<<< orphan*/  sq64; } ;
struct TYPE_20__ {int /*<<< orphan*/  uq32; int /*<<< orphan*/  sq32; } ;
struct TYPE_19__ {long slong; unsigned long ulong; } ;
struct TYPE_18__ {scalar_t__ u64; int /*<<< orphan*/  s64; } ;
struct TYPE_17__ {size_t u32; int /*<<< orphan*/  s32; } ;
struct voistatdata_numeric {TYPE_10__ q64; TYPE_9__ q32; TYPE_8__ intlong; TYPE_7__ int64; TYPE_6__ int32; } ;
typedef  int /*<<< orphan*/  s64q_t ;
typedef  int /*<<< orphan*/  s32q_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_15__ {struct voistatdata_numeric ub; struct voistatdata_numeric lb; } ;

/* Variables and functions */
#define  BKT_EXP 140 
#define  BKT_LIN 139 
#define  BKT_LINEXP 138 
 int BKT_USR ; 
 int EINVAL ; 
 int /*<<< orphan*/  Q_GIVAL (int /*<<< orphan*/ ) ; 
 int Q_QADDI (int /*<<< orphan*/ *,scalar_t__) ; 
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
 scalar_t__ stats_pow_u64 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline int
stats_vss_hist_bkt_hlpr(struct vss_hist_hlpr_info *info, uint32_t curbkt,
    struct voistatdata_numeric *bkt_lb, struct voistatdata_numeric *bkt_ub)
{
	uint64_t step = 0;
	int error = 0;

	switch (info->scheme) {
	case BKT_LIN:
		step = info->lin.stepinc;
		break;
	case BKT_EXP:
		step = stats_pow_u64(info->exp.stepbase,
		    info->exp.stepexp + curbkt);
		break;
	case BKT_LINEXP:
		{
		uint64_t curstepexp = 1;

		switch (info->voi_dtype) {
		case VSD_DTYPE_INT_S32:
			while ((int32_t)stats_pow_u64(info->linexp.stepbase,
			    curstepexp) <= bkt_lb->int32.s32)
				curstepexp++;
			break;
		case VSD_DTYPE_INT_U32:
			while ((uint32_t)stats_pow_u64(info->linexp.stepbase,
			    curstepexp) <= bkt_lb->int32.u32)
				curstepexp++;
			break;
		case VSD_DTYPE_INT_S64:
			while ((int64_t)stats_pow_u64(info->linexp.stepbase,
			    curstepexp) <= bkt_lb->int64.s64)
				curstepexp++;
			break;
		case VSD_DTYPE_INT_U64:
			while ((uint64_t)stats_pow_u64(info->linexp.stepbase,
			    curstepexp) <= bkt_lb->int64.u64)
				curstepexp++;
			break;
		case VSD_DTYPE_INT_SLONG:
			while ((long)stats_pow_u64(info->linexp.stepbase,
			    curstepexp) <= bkt_lb->intlong.slong)
				curstepexp++;
			break;
		case VSD_DTYPE_INT_ULONG:
			while ((unsigned long)stats_pow_u64(info->linexp.stepbase,
			    curstepexp) <= bkt_lb->intlong.ulong)
				curstepexp++;
			break;
		case VSD_DTYPE_Q_S32:
			while ((s32q_t)stats_pow_u64(info->linexp.stepbase,
			    curstepexp) <= Q_GIVAL(bkt_lb->q32.sq32))
			break;
		case VSD_DTYPE_Q_U32:
			while ((u32q_t)stats_pow_u64(info->linexp.stepbase,
			    curstepexp) <= Q_GIVAL(bkt_lb->q32.uq32))
			break;
		case VSD_DTYPE_Q_S64:
			while ((s64q_t)stats_pow_u64(info->linexp.stepbase,
			    curstepexp) <= Q_GIVAL(bkt_lb->q64.sq64))
				curstepexp++;
			break;
		case VSD_DTYPE_Q_U64:
			while ((u64q_t)stats_pow_u64(info->linexp.stepbase,
			    curstepexp) <= Q_GIVAL(bkt_lb->q64.uq64))
				curstepexp++;
			break;
		default:
			break;
		}

		step = stats_pow_u64(info->linexp.stepbase, curstepexp) /
		    info->linexp.linstepdiv;
		if (step == 0)
			step = 1;
		break;
		}
	default:
		break;
	}

	if (info->scheme == BKT_USR) {
		*bkt_lb = info->usr.bkts[curbkt].lb;
		*bkt_ub = info->usr.bkts[curbkt].ub;
	} else if (step != 0) {
		switch (info->voi_dtype) {
		case VSD_DTYPE_INT_S32:
			bkt_ub->int32.s32 += (int32_t)step;
			break;
		case VSD_DTYPE_INT_U32:
			bkt_ub->int32.u32 += (uint32_t)step;
			break;
		case VSD_DTYPE_INT_S64:
			bkt_ub->int64.s64 += (int64_t)step;
			break;
		case VSD_DTYPE_INT_U64:
			bkt_ub->int64.u64 += (uint64_t)step;
			break;
		case VSD_DTYPE_INT_SLONG:
			bkt_ub->intlong.slong += (long)step;
			break;
		case VSD_DTYPE_INT_ULONG:
			bkt_ub->intlong.ulong += (unsigned long)step;
			break;
		case VSD_DTYPE_Q_S32:
			error = Q_QADDI(&bkt_ub->q32.sq32, step);
			break;
		case VSD_DTYPE_Q_U32:
			error = Q_QADDI(&bkt_ub->q32.uq32, step);
			break;
		case VSD_DTYPE_Q_S64:
			error = Q_QADDI(&bkt_ub->q64.sq64, step);
			break;
		case VSD_DTYPE_Q_U64:
			error = Q_QADDI(&bkt_ub->q64.uq64, step);
			break;
		default:
			break;
		}
	} else { /* info->scheme != BKT_USR && step == 0 */
		return (EINVAL);
	}

	return (error);
}
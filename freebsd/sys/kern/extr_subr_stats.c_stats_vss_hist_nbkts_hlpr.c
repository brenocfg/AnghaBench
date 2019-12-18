#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_14__ {int /*<<< orphan*/  uq64; int /*<<< orphan*/  sq64; } ;
struct TYPE_13__ {int /*<<< orphan*/  uq32; int /*<<< orphan*/  sq32; } ;
struct TYPE_12__ {int /*<<< orphan*/  ulong; int /*<<< orphan*/  slong; } ;
struct TYPE_11__ {int /*<<< orphan*/  u64; int /*<<< orphan*/  s64; } ;
struct TYPE_10__ {int /*<<< orphan*/  u32; int /*<<< orphan*/  s32; } ;
struct voistatdata_numeric {TYPE_7__ q64; TYPE_6__ q32; TYPE_5__ intlong; TYPE_4__ int64; TYPE_3__ int32; } ;
struct TYPE_9__ {int nbkts; TYPE_1__* bkts; } ;
struct vss_hist_hlpr_info {scalar_t__ scheme; int voi_dtype; int flags; struct voistatdata_numeric ub; TYPE_2__ usr; struct voistatdata_numeric lb; } ;
struct TYPE_8__ {struct voistatdata_numeric lb; } ;

/* Variables and functions */
 scalar_t__ BKT_USR ; 
 int Q_QGTQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
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
 int VSD_HIST_LBOUND_INF ; 
 int VSD_HIST_UBOUND_INF ; 
 scalar_t__ stats_vss_hist_bkt_hlpr (struct vss_hist_hlpr_info*,int /*<<< orphan*/ ,struct voistatdata_numeric*,struct voistatdata_numeric*) ; 

__attribute__((used)) static uint32_t
stats_vss_hist_nbkts_hlpr(struct vss_hist_hlpr_info *info)
{
	struct voistatdata_numeric bkt_lb, bkt_ub;
	uint32_t nbkts;
	int done;

	if (info->scheme == BKT_USR) {
		/* XXXLAS: Setting info->{lb,ub} from macro is tricky. */
		info->lb = info->usr.bkts[0].lb;
		info->ub = info->usr.bkts[info->usr.nbkts - 1].lb;
	}

	nbkts = 0;
	done = 0;
	bkt_ub = info->lb;

	do {
		bkt_lb = bkt_ub;
		if (stats_vss_hist_bkt_hlpr(info, nbkts++, &bkt_lb, &bkt_ub))
			return (0);

		if (info->scheme == BKT_USR)
			done = (nbkts == info->usr.nbkts);
		else {
			switch (info->voi_dtype) {
			case VSD_DTYPE_INT_S32:
				done = (bkt_ub.int32.s32 > info->ub.int32.s32);
				break;
			case VSD_DTYPE_INT_U32:
				done = (bkt_ub.int32.u32 > info->ub.int32.u32);
				break;
			case VSD_DTYPE_INT_S64:
				done = (bkt_ub.int64.s64 > info->ub.int64.s64);
				break;
			case VSD_DTYPE_INT_U64:
				done = (bkt_ub.int64.u64 > info->ub.int64.u64);
				break;
			case VSD_DTYPE_INT_SLONG:
				done = (bkt_ub.intlong.slong >
				    info->ub.intlong.slong);
				break;
			case VSD_DTYPE_INT_ULONG:
				done = (bkt_ub.intlong.ulong >
				    info->ub.intlong.ulong);
				break;
			case VSD_DTYPE_Q_S32:
				done = Q_QGTQ(bkt_ub.q32.sq32,
				    info->ub.q32.sq32);
				break;
			case VSD_DTYPE_Q_U32:
				done = Q_QGTQ(bkt_ub.q32.uq32,
				    info->ub.q32.uq32);
				break;
			case VSD_DTYPE_Q_S64:
				done = Q_QGTQ(bkt_ub.q64.sq64,
				    info->ub.q64.sq64);
				break;
			case VSD_DTYPE_Q_U64:
				done = Q_QGTQ(bkt_ub.q64.uq64,
				    info->ub.q64.uq64);
				break;
			default:
				return (0);
			}
		}
	} while (!done);

	if (info->flags & VSD_HIST_LBOUND_INF)
		nbkts++;
	if (info->flags & VSD_HIST_UBOUND_INF)
		nbkts++;

	return (nbkts);
}
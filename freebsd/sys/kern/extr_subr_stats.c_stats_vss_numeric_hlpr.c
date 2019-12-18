#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  void* u64q_t ;
typedef  void* u32q_t ;
struct vss_numeric_hlpr_info {int /*<<< orphan*/  prec; } ;
struct voistatspec {int stype; int vs_dtype; int /*<<< orphan*/ * iv; int /*<<< orphan*/  vsdsz; } ;
struct TYPE_10__ {int /*<<< orphan*/  uq64; int /*<<< orphan*/  sq64; } ;
struct TYPE_9__ {int /*<<< orphan*/  uq32; int /*<<< orphan*/  sq32; } ;
struct TYPE_8__ {long slong; unsigned long ulong; } ;
struct TYPE_7__ {int /*<<< orphan*/  u64; int /*<<< orphan*/  s64; } ;
struct TYPE_6__ {int /*<<< orphan*/  u32; int /*<<< orphan*/  s32; } ;
struct voistatdata_numeric {TYPE_5__ q64; TYPE_4__ q32; TYPE_3__ intlong; TYPE_2__ int64; TYPE_1__ int32; } ;
typedef  void* s64q_t ;
typedef  void* s32q_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  enum vsd_dtype { ____Placeholder_vsd_dtype } vsd_dtype ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 size_t LIM_MAX ; 
 size_t LIM_MIN ; 
 int /*<<< orphan*/  Q_CTRLINI (int /*<<< orphan*/ ) ; 
 void* Q_SCVAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  VSD_DTYPE_INT_S32 140 
#define  VSD_DTYPE_INT_S64 139 
#define  VSD_DTYPE_INT_SLONG 138 
#define  VSD_DTYPE_INT_U32 137 
#define  VSD_DTYPE_INT_U64 136 
#define  VSD_DTYPE_INT_ULONG 135 
#define  VSD_DTYPE_Q_S32 134 
#define  VSD_DTYPE_Q_S64 133 
#define  VSD_DTYPE_Q_U32 132 
#define  VSD_DTYPE_Q_U64 131 
#define  VS_STYPE_MAX 130 
#define  VS_STYPE_MIN 129 
#define  VS_STYPE_SUM 128 
 struct voistatdata_numeric** numeric_limits ; 
 struct voistatdata_numeric stats_ctor_vsd_numeric (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stats_realloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vsd_dtype2size ; 

int
stats_vss_numeric_hlpr(enum vsd_dtype voi_dtype, struct voistatspec *vss,
    struct vss_numeric_hlpr_info *info)
{
	struct voistatdata_numeric iv;

	switch (vss->stype) {
	case VS_STYPE_SUM:
		iv = stats_ctor_vsd_numeric(0);
		break;
	case VS_STYPE_MIN:
		iv = numeric_limits[LIM_MAX][voi_dtype];
		break;
	case VS_STYPE_MAX:
		iv = numeric_limits[LIM_MIN][voi_dtype];
		break;
	default:
		return (EINVAL);
	}

	vss->iv = stats_realloc(NULL, 0, vsd_dtype2size[voi_dtype], 0);
	if (vss->iv == NULL)
		return (ENOMEM);

	vss->vs_dtype = voi_dtype;
	vss->vsdsz = vsd_dtype2size[voi_dtype];
	switch (voi_dtype) {
	case VSD_DTYPE_INT_S32:
		*((int32_t *)vss->iv) = iv.int32.s32;
		break;
	case VSD_DTYPE_INT_U32:
		*((uint32_t *)vss->iv) = iv.int32.u32;
		break;
	case VSD_DTYPE_INT_S64:
		*((int64_t *)vss->iv) = iv.int64.s64;
		break;
	case VSD_DTYPE_INT_U64:
		*((uint64_t *)vss->iv) = iv.int64.u64;
		break;
	case VSD_DTYPE_INT_SLONG:
		*((long *)vss->iv) = iv.intlong.slong;
		break;
	case VSD_DTYPE_INT_ULONG:
		*((unsigned long *)vss->iv) = iv.intlong.ulong;
		break;
	case VSD_DTYPE_Q_S32:
		*((s32q_t *)vss->iv) = Q_SCVAL(iv.q32.sq32,
		    Q_CTRLINI(info->prec));
		break;
	case VSD_DTYPE_Q_U32:
		*((u32q_t *)vss->iv) = Q_SCVAL(iv.q32.uq32,
		    Q_CTRLINI(info->prec));
		break;
	case VSD_DTYPE_Q_S64:
		*((s64q_t *)vss->iv) = Q_SCVAL(iv.q64.sq64,
		    Q_CTRLINI(info->prec));
		break;
	case VSD_DTYPE_Q_U64:
		*((u64q_t *)vss->iv) = Q_SCVAL(iv.q64.uq64,
		    Q_CTRLINI(info->prec));
		break;
	default:
		break;
	}

	return (0);
}
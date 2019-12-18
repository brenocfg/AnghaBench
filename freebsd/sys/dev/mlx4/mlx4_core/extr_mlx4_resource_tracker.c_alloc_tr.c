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
typedef  int /*<<< orphan*/  u64 ;
struct res_common {int owner; } ;
typedef  enum mlx4_resource { ____Placeholder_mlx4_resource } mlx4_resource ;

/* Variables and functions */
#define  RES_COUNTER 137 
#define  RES_CQ 136 
#define  RES_EQ 135 
#define  RES_FS_RULE 134 
#define  RES_MAC 133 
#define  RES_MPT 132 
#define  RES_MTT 131 
#define  RES_QP 130 
#define  RES_SRQ 129 
#define  RES_XRCD 128 
 struct res_common* alloc_counter_tr (int /*<<< orphan*/ ,int) ; 
 struct res_common* alloc_cq_tr (int /*<<< orphan*/ ) ; 
 struct res_common* alloc_eq_tr (int /*<<< orphan*/ ) ; 
 struct res_common* alloc_fs_rule_tr (int /*<<< orphan*/ ,int) ; 
 struct res_common* alloc_mpt_tr (int /*<<< orphan*/ ,int) ; 
 struct res_common* alloc_mtt_tr (int /*<<< orphan*/ ,int) ; 
 struct res_common* alloc_qp_tr (int /*<<< orphan*/ ) ; 
 struct res_common* alloc_srq_tr (int /*<<< orphan*/ ) ; 
 struct res_common* alloc_xrcdn_tr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static struct res_common *alloc_tr(u64 id, enum mlx4_resource type, int slave,
				   int extra)
{
	struct res_common *ret;

	switch (type) {
	case RES_QP:
		ret = alloc_qp_tr(id);
		break;
	case RES_MPT:
		ret = alloc_mpt_tr(id, extra);
		break;
	case RES_MTT:
		ret = alloc_mtt_tr(id, extra);
		break;
	case RES_EQ:
		ret = alloc_eq_tr(id);
		break;
	case RES_CQ:
		ret = alloc_cq_tr(id);
		break;
	case RES_SRQ:
		ret = alloc_srq_tr(id);
		break;
	case RES_MAC:
		pr_err("implementation missing\n");
		return NULL;
	case RES_COUNTER:
		ret = alloc_counter_tr(id, extra);
		break;
	case RES_XRCD:
		ret = alloc_xrcdn_tr(id);
		break;
	case RES_FS_RULE:
		ret = alloc_fs_rule_tr(id, extra);
		break;
	default:
		return NULL;
	}
	if (ret)
		ret->owner = slave;

	return ret;
}
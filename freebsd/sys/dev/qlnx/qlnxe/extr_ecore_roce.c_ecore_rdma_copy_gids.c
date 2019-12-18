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
typedef  union ecore_gid {int dummy; } ecore_gid ;
typedef  size_t u32 ;
struct TYPE_4__ {int /*<<< orphan*/ * dwords; int /*<<< orphan*/  ipv4_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dwords; int /*<<< orphan*/  ipv4_addr; } ;
struct ecore_rdma_qp {scalar_t__ roce_mode; TYPE_2__ dgid; TYPE_1__ sgid; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 size_t OSAL_ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_CPU_TO_LE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MEMSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ROCE_V2_IPV4 ; 

__attribute__((used)) static void ecore_rdma_copy_gids(struct ecore_rdma_qp *qp, __le32 *src_gid,
				 __le32 *dst_gid) {
	u32 i;

	if (qp->roce_mode == ROCE_V2_IPV4) {
		/* The IPv4 addresses shall be aligned to the highest word.
		 * The lower words must be zero.
		 */
		OSAL_MEMSET(src_gid, 0, sizeof(union ecore_gid));
		OSAL_MEMSET(dst_gid, 0, sizeof(union ecore_gid));
		src_gid[3] = OSAL_CPU_TO_LE32(qp->sgid.ipv4_addr);
		dst_gid[3] = OSAL_CPU_TO_LE32(qp->dgid.ipv4_addr);
	} else {
		/* RoCE, and RoCE v2 - IPv6: GIDs and IPv6 addresses coincide in
		 * location and size
		 */
		for (i = 0; i < OSAL_ARRAY_SIZE(qp->sgid.dwords); i++) {
			src_gid[i] = OSAL_CPU_TO_LE32(qp->sgid.dwords[i]);
			dst_gid[i] = OSAL_CPU_TO_LE32(qp->dgid.dwords[i]);
		}
	}
}
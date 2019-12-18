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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct ibv_sge {int length; int addr; scalar_t__ lkey; } ;
struct fw_ri_isgl {scalar_t__ r2; int /*<<< orphan*/  nsge; scalar_t__ r1; int /*<<< orphan*/  op; scalar_t__ sge; } ;
typedef  scalar_t__ __be64 ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  FW_RI_DATA_ISGL ; 
 int /*<<< orphan*/  htobe16 (int) ; 
 void* htobe64 (int) ; 

__attribute__((used)) static int build_isgl(struct fw_ri_isgl *isglp, struct ibv_sge *sg_list,
		      int num_sge, u32 *plenp)
{
	int i;
	u32 plen = 0;
	__be64 *flitp = (__be64 *)isglp->sge;

	for (i = 0; i < num_sge; i++) {
		if ((plen + sg_list[i].length) < plen)
			return -EMSGSIZE;
		plen += sg_list[i].length;
		*flitp++ = htobe64(((u64)sg_list[i].lkey << 32) |
				     sg_list[i].length);
		*flitp++ = htobe64(sg_list[i].addr);
	}
	*flitp = 0;
	isglp->op = FW_RI_DATA_ISGL;
	isglp->r1 = 0;
	isglp->nsge = htobe16(num_sge);
	isglp->r2 = 0;
	if (plenp)
		*plenp = plen;
	return 0;
}
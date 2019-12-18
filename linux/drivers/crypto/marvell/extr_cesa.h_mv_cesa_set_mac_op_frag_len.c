#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mac_digest; } ;
struct mv_cesa_op_ctx {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CESA_SA_DESC_MAC_FRAG_LEN (int) ; 
 int /*<<< orphan*/  CESA_SA_DESC_MAC_FRAG_LEN_MSK ; 

__attribute__((used)) static inline void mv_cesa_set_mac_op_frag_len(struct mv_cesa_op_ctx *op,
					       int len)
{
	op->desc.mac_digest &= ~CESA_SA_DESC_MAC_FRAG_LEN_MSK;
	op->desc.mac_digest |= CESA_SA_DESC_MAC_FRAG_LEN(len);
}
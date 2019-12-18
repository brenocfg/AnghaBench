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
struct mv_cesa_op_ctx {int dummy; } ;

/* Variables and functions */
 int CESA_SA_DESC_CFG_FIRST_FRAG ; 
 int CESA_SA_DESC_CFG_FRAG_MSK ; 
 int mv_cesa_get_op_cfg (struct mv_cesa_op_ctx const*) ; 

__attribute__((used)) static inline bool mv_cesa_mac_op_is_first_frag(const struct mv_cesa_op_ctx *op)
{
	return (mv_cesa_get_op_cfg(op) & CESA_SA_DESC_CFG_FRAG_MSK) ==
		CESA_SA_DESC_CFG_FIRST_FRAG;
}
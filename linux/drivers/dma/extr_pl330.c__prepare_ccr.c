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
typedef  int u32 ;
struct pl330_reqcfg {int brst_len; int brst_size; int scctl; int dcctl; int swap; scalar_t__ insnaccess; scalar_t__ nonsecure; scalar_t__ privileged; scalar_t__ dst_inc; scalar_t__ src_inc; } ;

/* Variables and functions */
 int CC_DSTBRSTLEN_SHFT ; 
 int CC_DSTBRSTSIZE_SHFT ; 
 int CC_DSTCCTRL_SHFT ; 
 int CC_DSTIA ; 
 int CC_DSTINC ; 
 int CC_DSTNS ; 
 int CC_DSTPRI ; 
 int CC_SRCBRSTLEN_SHFT ; 
 int CC_SRCBRSTSIZE_SHFT ; 
 int CC_SRCCCTRL_SHFT ; 
 int CC_SRCIA ; 
 int CC_SRCINC ; 
 int CC_SRCNS ; 
 int CC_SRCPRI ; 
 int CC_SWAP_SHFT ; 

__attribute__((used)) static inline u32 _prepare_ccr(const struct pl330_reqcfg *rqc)
{
	u32 ccr = 0;

	if (rqc->src_inc)
		ccr |= CC_SRCINC;

	if (rqc->dst_inc)
		ccr |= CC_DSTINC;

	/* We set same protection levels for Src and DST for now */
	if (rqc->privileged)
		ccr |= CC_SRCPRI | CC_DSTPRI;
	if (rqc->nonsecure)
		ccr |= CC_SRCNS | CC_DSTNS;
	if (rqc->insnaccess)
		ccr |= CC_SRCIA | CC_DSTIA;

	ccr |= (((rqc->brst_len - 1) & 0xf) << CC_SRCBRSTLEN_SHFT);
	ccr |= (((rqc->brst_len - 1) & 0xf) << CC_DSTBRSTLEN_SHFT);

	ccr |= (rqc->brst_size << CC_SRCBRSTSIZE_SHFT);
	ccr |= (rqc->brst_size << CC_DSTBRSTSIZE_SHFT);

	ccr |= (rqc->scctl << CC_SRCCCTRL_SHFT);
	ccr |= (rqc->dcctl << CC_DSTCCTRL_SHFT);

	ccr |= (rqc->swap << CC_SWAP_SHFT);

	return ccr;
}
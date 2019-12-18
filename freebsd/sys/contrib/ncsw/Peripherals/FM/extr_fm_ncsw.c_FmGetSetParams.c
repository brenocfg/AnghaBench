#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
struct TYPE_11__ {int type; int fm_cld; int fmqm_gs; int fm_npi; int fmfp_extc; } ;
struct TYPE_9__ {int type; scalar_t__ sleep; } ;
struct TYPE_13__ {TYPE_3__ getParams; TYPE_1__ setParams; } ;
typedef  TYPE_5__ t_FmGetSetParams ;
struct TYPE_14__ {TYPE_4__* p_FmFpmRegs; TYPE_2__* p_FmQmiRegs; scalar_t__ baseAddr; } ;
typedef  TYPE_6__ t_Fm ;
struct TYPE_15__ {int /*<<< orphan*/  iready; } ;
typedef  TYPE_7__ t_FMIramRegs ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_12__ {int /*<<< orphan*/  fmfp_extc; int /*<<< orphan*/  fm_npi; int /*<<< orphan*/  fm_cld; int /*<<< orphan*/  fmfp_brkc; } ;
struct TYPE_10__ {int /*<<< orphan*/  fmqm_gs; } ;

/* Variables and functions */
 int CLEAR_IRAM_READY ; 
 int /*<<< orphan*/  E_OK ; 
 scalar_t__ FM_MM_IMEM ; 
 int FPM_BRKC_SLP ; 
 int GET_FMFP_EXTC ; 
 int GET_FMQM_GS ; 
 int GET_FM_CLD ; 
 int GET_FM_NPI ; 
 int GET_UINT32 (int /*<<< orphan*/ ) ; 
 int IRAM_READY ; 
 scalar_t__ UINT_TO_PTR (scalar_t__) ; 
 int UPDATE_FM_CLD ; 
 int UPDATE_FPM_BRKC_SLP ; 
 int UPDATE_FPM_EXTC ; 
 int UPDATE_FPM_EXTC_CLEAR ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int) ; 

t_Error FmGetSetParams(t_Handle h_Fm, t_FmGetSetParams *p_Params)
{
	t_Fm* p_Fm = (t_Fm*)h_Fm;
	if (p_Params->setParams.type & UPDATE_FM_CLD)
	{
		WRITE_UINT32(p_Fm->p_FmFpmRegs->fm_cld, GET_UINT32(
				p_Fm->p_FmFpmRegs->fm_cld) | 0x00000800);
	}
	if (p_Params->setParams.type & CLEAR_IRAM_READY)
	{
	    t_FMIramRegs *p_Iram = (t_FMIramRegs *)UINT_TO_PTR(p_Fm->baseAddr + FM_MM_IMEM);
		WRITE_UINT32(p_Iram->iready,GET_UINT32(p_Iram->iready) & ~IRAM_READY);
	}
	if (p_Params->setParams.type & UPDATE_FPM_EXTC)
		WRITE_UINT32(p_Fm->p_FmFpmRegs->fmfp_extc,0x80000000);
	if (p_Params->setParams.type & UPDATE_FPM_EXTC_CLEAR)
		WRITE_UINT32(p_Fm->p_FmFpmRegs->fmfp_extc,0x00800000);
	if (p_Params->setParams.type & UPDATE_FPM_BRKC_SLP)
	{	
		if (p_Params->setParams.sleep)
			WRITE_UINT32(p_Fm->p_FmFpmRegs->fmfp_brkc, GET_UINT32(
				p_Fm->p_FmFpmRegs->fmfp_brkc) | FPM_BRKC_SLP);
		else
			WRITE_UINT32(p_Fm->p_FmFpmRegs->fmfp_brkc, GET_UINT32(
				p_Fm->p_FmFpmRegs->fmfp_brkc) & ~FPM_BRKC_SLP);
	}
	if (p_Params->getParams.type & GET_FM_CLD)
		p_Params->getParams.fm_cld = GET_UINT32(p_Fm->p_FmFpmRegs->fm_cld);
	if (p_Params->getParams.type & GET_FMQM_GS)
		p_Params->getParams.fmqm_gs = GET_UINT32(p_Fm->p_FmQmiRegs->fmqm_gs);
	if (p_Params->getParams.type & GET_FM_NPI)
		p_Params->getParams.fm_npi = GET_UINT32(p_Fm->p_FmFpmRegs->fm_npi);
	if (p_Params->getParams.type & GET_FMFP_EXTC)
		p_Params->getParams.fmfp_extc = GET_UINT32(p_Fm->p_FmFpmRegs->fmfp_extc);
	return E_OK;
}
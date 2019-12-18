#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_8__ {TYPE_2__* bmi_regs; } ;
struct TYPE_9__ {scalar_t__ portType; TYPE_3__ port; struct TYPE_9__* p_FmPortDriverParam; } ;
typedef  TYPE_4__ t_FmPort ;
struct TYPE_6__ {int fmbm_tfca; } ;
struct TYPE_7__ {TYPE_1__ tx; } ;

/* Variables and functions */
 int BMI_CMD_ATTR_MACCMD_MASK ; 
 int BMI_CMD_ATTR_MACCMD_SC_MASK ; 
 int BMI_CMD_ATTR_MACCMD_SC_SHIFT ; 
 int BMI_CMD_ATTR_MACCMD_SECURED ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_OPERATION ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int GET_UINT32 (int volatile) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int volatile,int) ; 
 scalar_t__ e_FM_PORT_TYPE_TX ; 
 scalar_t__ e_FM_PORT_TYPE_TX_10G ; 

void FmPortSetMacsecCmd(t_Handle h_FmPort, uint8_t dfltSci)
{
    t_FmPort *p_FmPort = (t_FmPort*)h_FmPort;
    volatile uint32_t *p_BmiCfgReg = NULL;
    uint32_t tmpReg;

    SANITY_CHECK_RETURN(p_FmPort, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN(p_FmPort->p_FmPortDriverParam, E_INVALID_STATE);

    if ((p_FmPort->portType != e_FM_PORT_TYPE_TX_10G)
            && (p_FmPort->portType != e_FM_PORT_TYPE_TX))
    {
        REPORT_ERROR(MAJOR, E_INVALID_OPERATION, ("The routine is relevant for Tx ports only"));
        return;
    }

    p_BmiCfgReg = &p_FmPort->port.bmi_regs->tx.fmbm_tfca;
    tmpReg = GET_UINT32(*p_BmiCfgReg) & ~BMI_CMD_ATTR_MACCMD_MASK;
    tmpReg |= BMI_CMD_ATTR_MACCMD_SECURED;
    tmpReg |= (((uint32_t)dfltSci << BMI_CMD_ATTR_MACCMD_SC_SHIFT)
            & BMI_CMD_ATTR_MACCMD_SC_MASK);

    WRITE_UINT32(*p_BmiCfgReg, tmpReg);
}
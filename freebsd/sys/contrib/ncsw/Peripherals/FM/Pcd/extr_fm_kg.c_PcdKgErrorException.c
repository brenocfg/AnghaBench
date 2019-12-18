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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_4__ {int /*<<< orphan*/  h_App; int /*<<< orphan*/  (* f_Exception ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* f_FmPcdIndexedException ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* p_FmPcdKg; int /*<<< orphan*/  h_Fm; } ;
typedef  TYPE_2__ t_FmPcd ;
struct fman_kg_regs {int dummy; } ;
struct TYPE_3__ {struct fman_kg_regs* p_FmPcdKgRegs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int /*<<< orphan*/ ) ; 
 int FM_EX_KG_DOUBLE_ECC ; 
 int FM_EX_KG_KEYSIZE_OVERFLOW ; 
 int /*<<< orphan*/  FmIsMaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_FM_PCD_KG_EXCEPTION_DOUBLE_ECC ; 
 int /*<<< orphan*/  e_FM_PCD_KG_EXCEPTION_KEYSIZE_OVERFLOW ; 
 int /*<<< orphan*/  fman_kg_get_event (struct fman_kg_regs*,int*,int*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PcdKgErrorException(t_Handle h_FmPcd)
{
    t_FmPcd                 *p_FmPcd = (t_FmPcd *)h_FmPcd;
    uint32_t                event,schemeIndexes = 0, index = 0;
    struct fman_kg_regs    *p_KgRegs;

    ASSERT_COND(FmIsMaster(p_FmPcd->h_Fm));
    p_KgRegs = p_FmPcd->p_FmPcdKg->p_FmPcdKgRegs;
    fman_kg_get_event(p_KgRegs, &event, &schemeIndexes);

    if (event & FM_EX_KG_DOUBLE_ECC)
        p_FmPcd->f_Exception(p_FmPcd->h_App,e_FM_PCD_KG_EXCEPTION_DOUBLE_ECC);
    if (event & FM_EX_KG_KEYSIZE_OVERFLOW)
    {
        if (schemeIndexes)
        {
            while (schemeIndexes)
            {
                if (schemeIndexes & 0x1)
                    p_FmPcd->f_FmPcdIndexedException(p_FmPcd->h_App,e_FM_PCD_KG_EXCEPTION_KEYSIZE_OVERFLOW, (uint16_t)(31 - index));
                schemeIndexes >>= 1;
                index+=1;
            }
        }
        else /* this should happen only when interrupt is forced. */
            p_FmPcd->f_Exception(p_FmPcd->h_App,e_FM_PCD_KG_EXCEPTION_KEYSIZE_OVERFLOW);
    }
}
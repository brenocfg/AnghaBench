#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* p_FmStateStruct; struct fman_fpm_regs* p_FmFpmRegs; } ;
typedef  TYPE_1__ t_Fm ;
struct fman_fpm_regs {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  enabledTimeStamp; int /*<<< orphan*/  fmClkFreq; struct TYPE_6__* count1MicroBit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_2__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fman_enable_time_stamp (struct fman_fpm_regs*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void EnableTimeStamp(t_Fm *p_Fm)
{
    struct fman_fpm_regs *fpm_rg = p_Fm->p_FmFpmRegs;

    ASSERT_COND(p_Fm->p_FmStateStruct);
    ASSERT_COND(p_Fm->p_FmStateStruct->count1MicroBit);

    fman_enable_time_stamp(fpm_rg, p_Fm->p_FmStateStruct->count1MicroBit, p_Fm->p_FmStateStruct->fmClkFreq);

    p_Fm->p_FmStateStruct->enabledTimeStamp = TRUE;
}
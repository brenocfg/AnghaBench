#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ resAddr; int /*<<< orphan*/  h_FmMuram; scalar_t__ fifoBaseAddr; scalar_t__ camBaseAddr; } ;
typedef  TYPE_1__ t_Fm ;

/* Variables and functions */
 int /*<<< orphan*/  FM_MURAM_FreeMem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT_TO_PTR (scalar_t__) ; 

__attribute__((used)) static void FreeInitResources(t_Fm *p_Fm)
{
    if (p_Fm->camBaseAddr)
       FM_MURAM_FreeMem(p_Fm->h_FmMuram, UINT_TO_PTR(p_Fm->camBaseAddr));
    if (p_Fm->fifoBaseAddr)
       FM_MURAM_FreeMem(p_Fm->h_FmMuram, UINT_TO_PTR(p_Fm->fifoBaseAddr));
    if (p_Fm->resAddr)
       FM_MURAM_FreeMem(p_Fm->h_FmMuram, UINT_TO_PTR(p_Fm->resAddr));
}
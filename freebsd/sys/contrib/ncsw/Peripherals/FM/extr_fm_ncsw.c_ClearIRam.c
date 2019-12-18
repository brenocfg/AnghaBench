#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* p_FmStateStruct; scalar_t__ baseAddr; } ;
typedef  TYPE_3__ t_Fm ;
struct TYPE_10__ {int /*<<< orphan*/  idata; int /*<<< orphan*/  iadd; } ;
typedef  TYPE_4__ t_FMIramRegs ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_7__ {int /*<<< orphan*/  minorRev; int /*<<< orphan*/  majorRev; } ;
struct TYPE_8__ {TYPE_1__ revInfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_3__*) ; 
 int /*<<< orphan*/  CORE_MemoryBarrier () ; 
 int /*<<< orphan*/  E_OK ; 
 int FM_IRAM_SIZE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FM_MM_IMEM ; 
 int GET_UINT32 (int /*<<< orphan*/ ) ; 
 int IRAM_IADD_AIE ; 
 scalar_t__ UINT_TO_PTR (scalar_t__) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static t_Error ClearIRam(t_Fm *p_Fm)
{
    t_FMIramRegs    *p_Iram;
    int             i;
    int             iram_size;

    ASSERT_COND(p_Fm);
    p_Iram = (t_FMIramRegs *)UINT_TO_PTR(p_Fm->baseAddr + FM_MM_IMEM);
    iram_size = FM_IRAM_SIZE(p_Fm->p_FmStateStruct->revInfo.majorRev,p_Fm->p_FmStateStruct->revInfo.minorRev);

    /* Enable the auto-increment */
    WRITE_UINT32(p_Iram->iadd, IRAM_IADD_AIE);
    while (GET_UINT32(p_Iram->iadd) != IRAM_IADD_AIE) ;

    for (i=0; i < (iram_size/4); i++)
        WRITE_UINT32(p_Iram->idata, 0xffffffff);

    WRITE_UINT32(p_Iram->iadd, iram_size - 4);
    CORE_MemoryBarrier();
    while (GET_UINT32(p_Iram->idata) != 0xffffffff) ;

    return E_OK;
}
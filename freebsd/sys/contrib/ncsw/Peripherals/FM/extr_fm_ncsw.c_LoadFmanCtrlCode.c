#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int size; int* p_Code; } ;
struct TYPE_7__ {TYPE_1__ firmware; scalar_t__ fwVerify; scalar_t__ baseAddr; } ;
typedef  TYPE_2__ t_Fm ;
struct TYPE_8__ {int /*<<< orphan*/  iready; int /*<<< orphan*/  iadd; int /*<<< orphan*/  idata; } ;
typedef  TYPE_3__ t_FMIramRegs ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_2__*) ; 
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  E_WRITE_FAILED ; 
 scalar_t__ FM_MM_IMEM ; 
 int GET_UINT32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFO ; 
 int IRAM_IADD_AIE ; 
 int IRAM_READY ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ UINT_TO_PTR (scalar_t__) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XX_UDelay (int) ; 

__attribute__((used)) static t_Error LoadFmanCtrlCode(t_Fm *p_Fm)
{
    t_FMIramRegs    *p_Iram;
    int             i;
    uint32_t        tmp;
    uint8_t         compTo16;

    ASSERT_COND(p_Fm);
    p_Iram = (t_FMIramRegs *)UINT_TO_PTR(p_Fm->baseAddr + FM_MM_IMEM);

    /* Enable the auto-increment */
    WRITE_UINT32(p_Iram->iadd, IRAM_IADD_AIE);
    while (GET_UINT32(p_Iram->iadd) != IRAM_IADD_AIE) ;

    for (i=0; i < (p_Fm->firmware.size / 4); i++)
        WRITE_UINT32(p_Iram->idata, p_Fm->firmware.p_Code[i]);

    compTo16 = (uint8_t)(p_Fm->firmware.size % 16);
    if (compTo16)
        for (i=0; i < ((16-compTo16) / 4); i++)
            WRITE_UINT32(p_Iram->idata, 0xffffffff);

    WRITE_UINT32(p_Iram->iadd,p_Fm->firmware.size-4);
    while (GET_UINT32(p_Iram->iadd) != (p_Fm->firmware.size-4)) ;

    /* verify that writing has completed */
    while (GET_UINT32(p_Iram->idata) != p_Fm->firmware.p_Code[(p_Fm->firmware.size / 4)-1]) ;

    if (p_Fm->fwVerify)
    {
        WRITE_UINT32(p_Iram->iadd, IRAM_IADD_AIE);
        while (GET_UINT32(p_Iram->iadd) != IRAM_IADD_AIE) ;
        for (i=0; i < (p_Fm->firmware.size / 4); i++)
        {
            tmp = GET_UINT32(p_Iram->idata);
            if (tmp != p_Fm->firmware.p_Code[i])
                RETURN_ERROR(MAJOR, E_WRITE_FAILED,
                             ("UCode write error : write 0x%x, read 0x%x",
                              p_Fm->firmware.p_Code[i],tmp));
        }
        WRITE_UINT32(p_Iram->iadd, 0x0);
    }

    /* Enable patch from IRAM */
    WRITE_UINT32(p_Iram->iready, IRAM_READY);
    XX_UDelay(1000);

    DBG(INFO, ("FMan-Controller code (ver %d.%d.%d) loaded to IRAM.",
               ((uint16_t *)p_Fm->firmware.p_Code)[2],
               ((uint8_t *)p_Fm->firmware.p_Code)[6],
               ((uint8_t *)p_Fm->firmware.p_Code)[7]));

    return E_OK;
}
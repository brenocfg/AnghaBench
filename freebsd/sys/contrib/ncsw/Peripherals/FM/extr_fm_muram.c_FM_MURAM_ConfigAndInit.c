#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* t_Handle ;
struct TYPE_7__ {uintptr_t baseAddr; struct TYPE_7__* h_Mem; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ t_FmMuram ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  MAJOR ; 
 scalar_t__ MM_Init (TYPE_1__**,uintptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XX_Free (TYPE_1__*) ; 
 scalar_t__ XX_Malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

t_Handle FM_MURAM_ConfigAndInit(uintptr_t baseAddress, uint32_t size)
{
    t_Handle    h_Mem;
    t_FmMuram   *p_FmMuram;

    if (!baseAddress)
    {
        REPORT_ERROR(MAJOR, E_INVALID_VALUE, ("baseAddress 0 is not supported"));
        return NULL;
    }

    if (baseAddress%4)
    {
        REPORT_ERROR(MAJOR, E_INVALID_VALUE, ("baseAddress not 4 bytes aligned!"));
        return NULL;
    }

    /* Allocate FM MURAM structure */
    p_FmMuram = (t_FmMuram *) XX_Malloc(sizeof(t_FmMuram));
    if (!p_FmMuram)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM MURAM driver structure"));
        return NULL;
    }
    memset(p_FmMuram, 0, sizeof(t_FmMuram));


    if ((MM_Init(&h_Mem, baseAddress, size) != E_OK) || (!h_Mem))
    {
        XX_Free(p_FmMuram);
        REPORT_ERROR(MAJOR, E_INVALID_HANDLE, ("FM-MURAM partition!!!"));
        return NULL;
    }

    /* Initialize FM MURAM parameters which will be kept by the driver */
    p_FmMuram->baseAddr = baseAddress;
    p_FmMuram->size = size;
    p_FmMuram->h_Mem = h_Mem;

    return p_FmMuram;
}
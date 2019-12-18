#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_5__ {TYPE_1__* intrMng; } ;
typedef  TYPE_2__ t_FmMacsec ;
typedef  int /*<<< orphan*/  e_FmMacsecEventModules ;
typedef  int /*<<< orphan*/  e_FmIntrType ;
struct TYPE_4__ {int /*<<< orphan*/ * h_SrcHandle; int /*<<< orphan*/ * f_Isr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  GET_MACSEC_MODULE_EVENT (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN (TYPE_2__*,int /*<<< orphan*/ ) ; 
 size_t e_FM_MACSEC_EV_DUMMY_LAST ; 

void FmMacsecUnregisterIntr(t_Handle                h_FmMacsec,
                            e_FmMacsecEventModules  module,
                            uint8_t                 modId,
                            e_FmIntrType            intrType)
{
    t_FmMacsec  *p_FmMacsec = (t_FmMacsec*)h_FmMacsec;
    uint8_t     event= 0;

    SANITY_CHECK_RETURN(p_FmMacsec, E_INVALID_HANDLE);

    GET_MACSEC_MODULE_EVENT(module, modId,intrType, event);

    ASSERT_COND(event != e_FM_MACSEC_EV_DUMMY_LAST);
    p_FmMacsec->intrMng[event].f_Isr = NULL;
    p_FmMacsec->intrMng[event].h_SrcHandle = NULL;
}
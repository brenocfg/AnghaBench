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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int t_Handle ;
struct TYPE_4__ {TYPE_1__* intrMng; } ;
typedef  TYPE_2__ t_Fm ;
typedef  int /*<<< orphan*/  e_FmIntrType ;
typedef  int /*<<< orphan*/  e_FmEventModules ;
struct TYPE_3__ {int /*<<< orphan*/ * h_SrcHandle; int /*<<< orphan*/  f_Isr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  GET_FM_MODULE_EVENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UnimplementedIsr ; 
 int e_FM_EV_DUMMY_LAST ; 

void FmUnregisterIntr(t_Handle                  h_Fm,
                        e_FmEventModules        module,
                        uint8_t                 modId,
                        e_FmIntrType            intrType)
{
    t_Fm        *p_Fm = (t_Fm*)h_Fm;
    int         event = 0;

    ASSERT_COND(h_Fm);

    GET_FM_MODULE_EVENT(module, modId,intrType, event);
    ASSERT_COND(event < e_FM_EV_DUMMY_LAST);

    p_Fm->intrMng[event].f_Isr = UnimplementedIsr;
    p_Fm->intrMng[event].h_SrcHandle = NULL;
}
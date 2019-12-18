#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
struct TYPE_6__ {scalar_t__ event_source; int application; } ;
typedef  TYPE_1__ gdt_evt_str ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  GDT_DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GDT_D_MISC ; 
 int GDT_MAX_EVENTS ; 
 int TRUE ; 
 TYPE_1__* ebuffer ; 
 int elastidx ; 
 int /*<<< orphan*/  elock ; 
 int eoldidx ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void gdt_readapp_event(u_int8_t application, gdt_evt_str *estr)
{
    gdt_evt_str *e;
    int found = FALSE;
    int eindex;
    
    GDT_DPRINTF(GDT_D_MISC, ("gdt_readapp_event(%d)\n", application));
    mtx_lock(&elock);
    eindex = eoldidx;
    for (;;) {
        e = &ebuffer[eindex];
        if (e->event_source == 0)
            break;
        if ((e->application & application) == 0) {
            e->application |= application;
            found = TRUE;
            break;
        }
        if (eindex == elastidx)
            break;
        if (++eindex == GDT_MAX_EVENTS)
            eindex = 0;
    }
    if (found)
        memcpy(estr, e, sizeof(gdt_evt_str));
    else
        estr->event_source = 0;
    mtx_unlock(&elock);
}
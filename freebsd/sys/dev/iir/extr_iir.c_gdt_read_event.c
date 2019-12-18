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
struct TYPE_6__ {scalar_t__ event_source; } ;
typedef  TYPE_1__ gdt_evt_str ;

/* Variables and functions */
 int /*<<< orphan*/  GDT_DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GDT_D_MISC ; 
 int GDT_MAX_EVENTS ; 
 TYPE_1__* ebuffer ; 
 int elastidx ; 
 int /*<<< orphan*/  elock ; 
 int eoldidx ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int gdt_read_event(int handle, gdt_evt_str *estr)
{
    gdt_evt_str *e;
    int eindex;
    
    GDT_DPRINTF(GDT_D_MISC, ("gdt_read_event(%d)\n", handle));
    mtx_lock(&elock);
    if (handle == -1)
        eindex = eoldidx;
    else
        eindex = handle;
    estr->event_source = 0;

    if (eindex >= GDT_MAX_EVENTS) {
	mtx_unlock(&elock);
        return eindex;
    }
    e = &ebuffer[eindex];
    if (e->event_source != 0) {
        if (eindex != elastidx) {
            if (++eindex == GDT_MAX_EVENTS)
                eindex = 0;
        } else {
            eindex = -1;
        }
        memcpy(estr, e, sizeof(gdt_evt_str));
    }
    mtx_unlock(&elock);
    return eindex;
}
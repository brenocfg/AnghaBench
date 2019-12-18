#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ t_BmPortal ;

/* Variables and functions */
 int BMAN_PORTAL_FLAG_IRQ_FAST ; 
 int /*<<< orphan*/  __poll_portal_fast (TYPE_1__*) ; 
 int /*<<< orphan*/  __poll_portal_slow (TYPE_1__*) ; 

__attribute__((used)) static void portal_isr(void *ptr)
{
    t_BmPortal *portal = ptr;
        /* Only do fast-path handling if it's required */
    if (portal->flags & BMAN_PORTAL_FLAG_IRQ_FAST)
        __poll_portal_fast(portal);
    __poll_portal_slow(portal);

}
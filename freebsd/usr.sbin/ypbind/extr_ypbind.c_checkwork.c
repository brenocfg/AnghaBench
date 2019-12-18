#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct _dom_binding {struct _dom_binding* dom_pnext; } ;

/* Variables and functions */
 int /*<<< orphan*/  ping (struct _dom_binding*) ; 
 struct _dom_binding* ypbindlist ; 

void
checkwork(void)
{
	struct _dom_binding *ypdb;

	for (ypdb = ypbindlist; ypdb; ypdb = ypdb->dom_pnext)
		ping(ypdb);
}
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
struct auditfilter_module {int /*<<< orphan*/ * am_dlhandle; int /*<<< orphan*/ * am_cookie; int /*<<< orphan*/  (* am_detach ) (struct auditfilter_module*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dlclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct auditfilter_module*) ; 

__attribute__((used)) static void
auditfilter_module_detach(struct auditfilter_module *am)
{

	if (am->am_detach != NULL)
		am->am_detach(am);
	am->am_cookie = NULL;
	(void)dlclose(am->am_dlhandle);
	am->am_dlhandle = NULL;
}
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
struct auditfilter_module {void* am_cookie; } ;

/* Variables and functions */

void
audit_filter_setcookie(void *instance, void *cookie)
{
	struct auditfilter_module *am;

	am = (struct auditfilter_module *)instance;
	am->am_cookie = cookie;
}
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
struct wpa_cred {scalar_t__ priority; scalar_t__ sp_priority; int /*<<< orphan*/ * provisioning_sp; } ;

/* Variables and functions */
 scalar_t__ os_strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cred_prio_cmp(const struct wpa_cred *a, const struct wpa_cred *b)
{
	if (a->priority > b->priority)
		return 1;
	if (a->priority < b->priority)
		return -1;
	if (a->provisioning_sp == NULL || b->provisioning_sp == NULL ||
	    os_strcmp(a->provisioning_sp, b->provisioning_sp) != 0)
		return 0;
	if (a->sp_priority < b->sp_priority)
		return 1;
	if (a->sp_priority > b->sp_priority)
		return -1;
	return 0;
}
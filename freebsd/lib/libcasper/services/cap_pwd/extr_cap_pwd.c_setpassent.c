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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/ * cap_xfer_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  nvlist_add_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/ *,char*) ; 

int
cap_setpassent(cap_channel_t *chan, int stayopen)
{
	nvlist_t *nvl;

	nvl = nvlist_create(0);
	nvlist_add_string(nvl, "cmd", "setpassent");
	nvlist_add_bool(nvl, "stayopen", stayopen != 0);
	nvl = cap_xfer_nvlist(chan, nvl);
	if (nvl == NULL)
		return (0);
	if (nvlist_get_number(nvl, "error") != 0) {
		errno = nvlist_get_number(nvl, "error");
		nvlist_destroy(nvl);
		return (0);
	}
	nvlist_destroy(nvl);

	return (1);
}
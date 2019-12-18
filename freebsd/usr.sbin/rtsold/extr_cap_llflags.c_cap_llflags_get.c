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
 scalar_t__ dnvlist_get_number (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int llflags_get (char const*,int*) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/ *,char*) ; 

int
cap_llflags_get(cap_channel_t *cap, const char *ifname, int *flagsp)
{
#ifdef WITH_CASPER
	nvlist_t *nvl;
	int error;

	nvl = nvlist_create(0);
	nvlist_add_string(nvl, "cmd", "get");
	nvlist_add_string(nvl, "ifname", ifname);
	nvl = cap_xfer_nvlist(cap, nvl);
	if (nvl == NULL)
		return (-1);
	error = (int)dnvlist_get_number(nvl, "error", 0);
	if (error == 0)
		*flagsp = (int)nvlist_get_number(nvl, "flags");
	nvlist_destroy(nvl);
	if (error != 0)
		errno = error;
	return (error == 0 ? 0 : -1);
#else
	(void)cap;
	return (llflags_get(ifname, flagsp));
#endif
}
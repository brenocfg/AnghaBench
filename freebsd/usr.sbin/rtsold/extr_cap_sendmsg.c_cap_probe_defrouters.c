#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ifinfo {int /*<<< orphan*/  linkid; TYPE_1__* sdl; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  cap_channel_t ;
struct TYPE_2__ {int /*<<< orphan*/  sdl_index; } ;

/* Variables and functions */
 int /*<<< orphan*/ * cap_xfer_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dnvlist_get_number (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 int probe_defrouters (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
cap_probe_defrouters(cap_channel_t *cap, struct ifinfo *ifinfo)
{
#ifdef WITH_CASPER
	nvlist_t *nvl;
	int error;

	nvl = nvlist_create(0);
	nvlist_add_string(nvl, "cmd", "probe_defrouters");
	nvlist_add_number(nvl, "ifindex", ifinfo->sdl->sdl_index);
	nvlist_add_number(nvl, "linkid", ifinfo->linkid);

	nvl = cap_xfer_nvlist(cap, nvl);
	if (nvl == NULL)
		return (errno);
	error = (int)dnvlist_get_number(nvl, "error", 0);
	nvlist_destroy(nvl);
	errno = error;
	return (error == 0 ? 0 : -1);
#else
	(void)cap;
	return (probe_defrouters(ifinfo->sdl->sdl_index, ifinfo->linkid));
#endif
}
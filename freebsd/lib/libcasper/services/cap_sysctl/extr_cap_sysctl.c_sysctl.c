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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int do_sysctl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,size_t*,void const*,size_t) ; 
 int /*<<< orphan*/  nvlist_add_binary (int /*<<< orphan*/ *,char*,int const*,size_t) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 

int
cap_sysctl(cap_channel_t *chan, const int *name, u_int namelen, void *oldp,
    size_t *oldlenp, const void *newp, size_t newlen)
{
	nvlist_t *req;

	req = nvlist_create(0);
	nvlist_add_string(req, "cmd", "sysctl");
	nvlist_add_binary(req, "mib", name, (size_t)namelen * sizeof(int));
	return (do_sysctl(chan, req, oldp, oldlenp, newp, newlen));
}
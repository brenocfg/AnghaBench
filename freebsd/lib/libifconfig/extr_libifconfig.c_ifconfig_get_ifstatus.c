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
struct ifstat {int /*<<< orphan*/  ifs_name; } ;
typedef  int /*<<< orphan*/  ifconfig_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  SIOCGIFSTATUS ; 
 int ifconfig_ioctlwrap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifstat*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

int
ifconfig_get_ifstatus(ifconfig_handle_t *h, const char *name,
    struct ifstat *ifs)
{
	strlcpy(ifs->ifs_name, name, sizeof(ifs->ifs_name));
	return (ifconfig_ioctlwrap(h, AF_LOCAL, SIOCGIFSTATUS, ifs));
}
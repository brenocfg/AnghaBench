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
struct ifconfig_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ifconfig_close (struct ifconfig_handle*) ; 
 scalar_t__ ifconfig_get_orig_name (struct ifconfig_handle*,char*,char**) ; 
 struct ifconfig_handle* ifconfig_open () ; 
 int /*<<< orphan*/  setoid (char*,size_t,char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static void
get_orig_iface_name(char *oid, size_t oid_size, char *name)
{
	struct ifconfig_handle *h;
	char *orig_name;

	h = ifconfig_open();
	if (ifconfig_get_orig_name(h, name, &orig_name) < 0) {
		/* check for original interface name. */
		orig_name = name;
	}

	if (strlen(orig_name) < strlen("wlan") + 1 ||
	    strncmp(orig_name, "wlan", 4) != 0)
		errx(1, "expecting a wlan interface name");

	ifconfig_close(h);
	setoid(oid, oid_size, orig_name);
	if (orig_name != name)
		free(orig_name);
}
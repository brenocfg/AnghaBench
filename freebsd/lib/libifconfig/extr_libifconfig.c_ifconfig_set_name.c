#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ifreq {char* ifr_data; int /*<<< orphan*/  ifr_name; } ;
typedef  int /*<<< orphan*/  ifr ;
struct TYPE_5__ {int /*<<< orphan*/  errcode; int /*<<< orphan*/  errtype; } ;
struct TYPE_6__ {TYPE_1__ error; } ;
typedef  TYPE_2__ ifconfig_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  OTHER ; 
 int /*<<< orphan*/  SIOCSIFNAME ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ ifconfig_ioctlwrap (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

int
ifconfig_set_name(ifconfig_handle_t *h, const char *name, const char *newname)
{
	struct ifreq ifr;
	char *tmpname;

	memset(&ifr, 0, sizeof(ifr));
	tmpname = strdup(newname);
	if (tmpname == NULL) {
		h->error.errtype = OTHER;
		h->error.errcode = ENOMEM;
		return (-1);
	}

	(void)strlcpy(ifr.ifr_name, name, sizeof(ifr.ifr_name));
	ifr.ifr_data = tmpname;
	if (ifconfig_ioctlwrap(h, AF_LOCAL, SIOCSIFNAME, &ifr) != 0) {
		free(tmpname);
		return (-1);
	}

	free(tmpname);
	return (0);
}
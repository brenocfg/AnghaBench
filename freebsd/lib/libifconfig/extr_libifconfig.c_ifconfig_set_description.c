#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int length; int /*<<< orphan*/ * buffer; } ;
struct ifreq {TYPE_2__ ifr_buffer; int /*<<< orphan*/  ifr_name; } ;
typedef  int /*<<< orphan*/  ifr ;
struct TYPE_7__ {int /*<<< orphan*/  errcode; int /*<<< orphan*/  errtype; } ;
struct TYPE_9__ {TYPE_1__ error; } ;
typedef  TYPE_3__ ifconfig_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  OTHER ; 
 int /*<<< orphan*/  SIOCSIFDESCR ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ ifconfig_ioctlwrap (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 
 int ifconfig_unset_description (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int strlen (char const*) ; 

int
ifconfig_set_description(ifconfig_handle_t *h, const char *name,
    const char *newdescription)
{
	struct ifreq ifr;
	int desclen;

	memset(&ifr, 0, sizeof(ifr));
	desclen = strlen(newdescription);

	/*
	 * Unset description if the new description is 0 characters long.
	 * TODO: Decide whether this should be an error condition instead.
	 */
	if (desclen == 0) {
		return (ifconfig_unset_description(h, name));
	}

	(void)strlcpy(ifr.ifr_name, name, sizeof(ifr.ifr_name));
	ifr.ifr_buffer.length = desclen + 1;
	ifr.ifr_buffer.buffer = strdup(newdescription);

	if (ifr.ifr_buffer.buffer == NULL) {
		h->error.errtype = OTHER;
		h->error.errcode = ENOMEM;
		return (-1);
	}

	if (ifconfig_ioctlwrap(h, AF_LOCAL, SIOCSIFDESCR, &ifr) != 0) {
		free(ifr.ifr_buffer.buffer);
		return (-1);
	}

	free(ifr.ifr_buffer.buffer);
	return (0);
}
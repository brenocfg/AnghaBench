#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pcap_dbus {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  setnonblock_op; int /*<<< orphan*/  getnonblock_op; int /*<<< orphan*/  activate_op; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  dbus_activate ; 
 int /*<<< orphan*/  dbus_getnonblock ; 
 int /*<<< orphan*/  dbus_setnonblock ; 
 TYPE_1__* pcap_create_common (char*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

pcap_t *
dbus_create(const char *device, char *ebuf, int *is_ours)
{
	pcap_t *p;

	if (strcmp(device, "dbus-system") &&
		strcmp(device, "dbus-session") &&
		strncmp(device, "dbus://", 7))
	{
		*is_ours = 0;
		return NULL;
	}

	*is_ours = 1;
	p = pcap_create_common(ebuf, sizeof (struct pcap_dbus));
	if (p == NULL)
		return (NULL);

	p->activate_op = dbus_activate;
	/*
	 * Set these up front, so that, even if our client tries
	 * to set non-blocking mode before we're activated, or
	 * query the state of non-blocking mode, they get an error,
	 * rather than having the non-blocking mode option set
	 * for use later.
	 */
	p->getnonblock_op = dbus_getnonblock;
	p->setnonblock_op = dbus_setnonblock;
	return (p);
}
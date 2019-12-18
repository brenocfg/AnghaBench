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
struct pcap_bt {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  activate_op; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_IFACE ; 
 int /*<<< orphan*/  bt_activate ; 
 TYPE_1__* pcap_create_common (char*,int) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 char* strrchr (char const*,char) ; 
 long strtol (char const*,char**,int) ; 

pcap_t *
bt_create(const char *device, char *ebuf, int *is_ours)
{
	const char *cp;
	char *cpend;
	long devnum;
	pcap_t *p;

	/* Does this look like a Bluetooth device? */
	cp = strrchr(device, '/');
	if (cp == NULL)
		cp = device;
	/* Does it begin with BT_IFACE? */
	if (strncmp(cp, BT_IFACE, sizeof BT_IFACE - 1) != 0) {
		/* Nope, doesn't begin with BT_IFACE */
		*is_ours = 0;
		return NULL;
	}
	/* Yes - is BT_IFACE followed by a number? */
	cp += sizeof BT_IFACE - 1;
	devnum = strtol(cp, &cpend, 10);
	if (cpend == cp || *cpend != '\0') {
		/* Not followed by a number. */
		*is_ours = 0;
		return NULL;
	}
	if (devnum < 0) {
		/* Followed by a non-valid number. */
		*is_ours = 0;
		return NULL;
	}

	/* OK, it's probably ours. */
	*is_ours = 1;

	p = pcap_create_common(ebuf, sizeof (struct pcap_bt));
	if (p == NULL)
		return (NULL);

	p->activate_op = bt_activate;
	return (p);
}
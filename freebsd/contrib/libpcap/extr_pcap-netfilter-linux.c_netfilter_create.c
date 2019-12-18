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
struct pcap_netfilter {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  activate_op; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  NFLOG_IFACE ; 
 int /*<<< orphan*/  NFQUEUE_IFACE ; 
 int /*<<< orphan*/  netfilter_activate ; 
 TYPE_1__* pcap_create_common (char*,int) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 char* strrchr (char const*,char) ; 

pcap_t *
netfilter_create(const char *device, char *ebuf, int *is_ours)
{
	const char *cp;
	pcap_t *p;

	/* Does this look like an netfilter device? */
	cp = strrchr(device, '/');
	if (cp == NULL)
		cp = device;

	/* Does it begin with NFLOG_IFACE or NFQUEUE_IFACE? */
	if (strncmp(cp, NFLOG_IFACE, sizeof NFLOG_IFACE - 1) == 0)
		cp += sizeof NFLOG_IFACE - 1;
	else if (strncmp(cp, NFQUEUE_IFACE, sizeof NFQUEUE_IFACE - 1) == 0)
		cp += sizeof NFQUEUE_IFACE - 1;
	else {
		/* Nope, doesn't begin with NFLOG_IFACE nor NFQUEUE_IFACE */
		*is_ours = 0;
		return NULL;
	}

	/*
	 * Yes - is that either the end of the name, or is it followed
	 * by a colon?
	 */
	if (*cp != ':' && *cp != '\0') {
		/* Nope */
		*is_ours = 0;
		return NULL;
	}

	/* OK, it's probably ours. */
	*is_ours = 1;

	p = pcap_create_common(ebuf, sizeof (struct pcap_netfilter));
	if (p == NULL)
		return (NULL);

	p->activate_op = netfilter_activate;
	return (p);
}
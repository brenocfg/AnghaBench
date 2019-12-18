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
struct pcap_septel {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  setnonblock_op; int /*<<< orphan*/  getnonblock_op; int /*<<< orphan*/  activate_op; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 TYPE_1__* pcap_create_common (char*,int) ; 
 int /*<<< orphan*/  septel_activate ; 
 int /*<<< orphan*/  septel_getnonblock ; 
 int /*<<< orphan*/  septel_setnonblock ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strrchr (char const*,char) ; 

pcap_t *septel_create(const char *device, char *ebuf, int *is_ours) {
	const char *cp;
	pcap_t *p;

	/* Does this look like the Septel device? */
	cp = strrchr(device, '/');
	if (cp == NULL)
		cp = device;
	if (strcmp(cp, "septel") != 0) {
		/* Nope, it's not "septel" */
		*is_ours = 0;
		return NULL;
	}

	/* OK, it's probably ours. */
	*is_ours = 1;

	p = pcap_create_common(ebuf, sizeof (struct pcap_septel));
	if (p == NULL)
		return NULL;

	p->activate_op = septel_activate;
	/*
	 * Set these up front, so that, even if our client tries
	 * to set non-blocking mode before we're activated, or
	 * query the state of non-blocking mode, they get an error,
	 * rather than having the non-blocking mode option set
	 * for use later.
	 */
	p->getnonblock_op = septel_getnonblock;
	p->setnonblock_op = septel_setnonblock;
	return p;
}
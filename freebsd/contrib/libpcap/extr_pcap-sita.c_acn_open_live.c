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
struct TYPE_5__ {int fd; TYPE_2__* iface; int /*<<< orphan*/ * ip; } ;
typedef  TYPE_1__ unit_t ;
typedef  int /*<<< orphan*/  pcap_if_list_t ;
struct TYPE_6__ {int iftype; struct TYPE_6__* next; scalar_t__ IOPname; scalar_t__ name; } ;
typedef  TYPE_2__ iface_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIVE ; 
 int MAX_CHASSIS ; 
 int MAX_GEOSLOT ; 
 scalar_t__ get_error_response (int,char*) ; 
 int /*<<< orphan*/  open_with_IOP (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_platform_finddevs (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  send_to_fd (int,scalar_t__,unsigned char*) ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 
 scalar_t__ strlen (scalar_t__) ; 
 TYPE_1__** units ; 

__attribute__((used)) static int acn_open_live(const char *name, char *errbuf, int *linktype) {		/* returns 0 on error, else returns the file descriptor */
	int			chassis, geoslot;
	unit_t		*u;
	iface_t		*p;
	pcap_if_list_t	devlist;

	pcap_platform_finddevs(&devlist, errbuf);
	for (chassis = 0; chassis <= MAX_CHASSIS; chassis++) {										/* scan the table... */
		for (geoslot = 0; geoslot <= MAX_GEOSLOT; geoslot++) {
			u = &units[chassis][geoslot];
			if (u->ip != NULL) {
				p = u->iface;
				while (p) {																		/* and all interfaces... */
					if (p->IOPname && p->name && (strcmp(p->name, name) == 0)) {				/* and if we found the interface we want... */
						*linktype = p->iftype;
						open_with_IOP(u, LIVE);													/* start a connection with that IOP */
						send_to_fd(u->fd, strlen(p->IOPname)+1, (unsigned char *)p->IOPname);	/* send the IOP's interface name, and a terminating null */
						if (get_error_response(u->fd, errbuf)) {
							return -1;
						}
						return u->fd;															/* and return that open descriptor */
					}
					p = p->next;
				}
			}
		}
	}
	return -1;																				/* if the interface wasn't found, return an error */
}
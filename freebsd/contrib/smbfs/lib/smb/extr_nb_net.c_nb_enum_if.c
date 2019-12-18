#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct nb_ifdesc {int id_flags; struct nb_ifdesc* id_next; int /*<<< orphan*/  id_mask; int /*<<< orphan*/  id_addr; int /*<<< orphan*/  id_name; } ;
struct ifaddrs {int ifa_flags; scalar_t__ ifa_netmask; TYPE_1__* ifa_addr; int /*<<< orphan*/  ifa_name; struct ifaddrs* ifa_next; } ;
struct TYPE_2__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int ENOMEM ; 
 int IFF_BROADCAST ; 
 int IFF_UP ; 
 int /*<<< orphan*/  bzero (struct nb_ifdesc*,int) ; 
 int errno ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 scalar_t__ getifaddrs (struct ifaddrs**) ; 
 struct nb_ifdesc* malloc (int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

int
nb_enum_if(struct nb_ifdesc **iflist, int maxif)
{  
	struct nb_ifdesc *ifd;
	struct ifaddrs *ifp, *p;
	int i;

	if (getifaddrs(&ifp) < 0)
		return errno;

	*iflist = NULL;
	i = 0;
	for (p = ifp; p; p = p->ifa_next) {

		if (i >= maxif)
			break;

		if ((p->ifa_addr->sa_family != AF_INET) ||
		    ((p->ifa_flags & (IFF_UP|IFF_BROADCAST))
		     != (IFF_UP|IFF_BROADCAST)))
			continue;
		if (strlen(p->ifa_name) >= sizeof(ifd->id_name))
			continue;

		ifd = malloc(sizeof(struct nb_ifdesc));
		if (ifd == NULL) {
			freeifaddrs(ifp);
			/* XXX should free stuff already in *iflist */
			return ENOMEM;
		}
		bzero(ifd, sizeof(struct nb_ifdesc));
		strcpy(ifd->id_name, p->ifa_name);
		ifd->id_flags = p->ifa_flags;
		ifd->id_addr = ((struct sockaddr_in *)p->ifa_addr)->sin_addr;
		ifd->id_mask = ((struct sockaddr_in *)p->ifa_netmask)->sin_addr;
		ifd->id_next = *iflist;
		*iflist = ifd;
		i++;
	}

	freeifaddrs(ifp);
	return 0;
}
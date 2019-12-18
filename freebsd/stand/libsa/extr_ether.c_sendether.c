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
typedef  int /*<<< orphan*/  uint8_t ;
struct iodesc {int /*<<< orphan*/ * myea; } ;
struct ether_header {int /*<<< orphan*/  ether_type; int /*<<< orphan*/  ether_dhost; int /*<<< orphan*/  ether_shost; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  MACPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  htons (int) ; 
 int netif_put (struct iodesc*,struct ether_header*,size_t) ; 
 int /*<<< orphan*/  printf (char*) ; 

ssize_t
sendether(struct iodesc *d, void *pkt, size_t len, uint8_t *dea, int etype)
{
	ssize_t n;
	struct ether_header *eh;

#ifdef ETHER_DEBUG
 	if (debug)
		printf("sendether: called\n");
#endif

	eh = (struct ether_header *)pkt - 1;
	len += sizeof(*eh);

	MACPY(d->myea, eh->ether_shost);		/* by byte */
	MACPY(dea, eh->ether_dhost);			/* by byte */
	eh->ether_type = htons(etype);

	n = netif_put(d, eh, len);
	if (n == -1 || n < sizeof(*eh))
		return (-1);

	n -= sizeof(*eh);
	return (n);
}
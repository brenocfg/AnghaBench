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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  time_t ;
struct iodesc {int /*<<< orphan*/  myea; } ;
struct ether_header {int /*<<< orphan*/  ether_type; int /*<<< orphan*/  ether_dhost; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ ETHER_ALIGN ; 
 int /*<<< orphan*/  bcea ; 
 scalar_t__ bcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ debug ; 
 char* ether_sprintf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int netif_get (struct iodesc*,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

ssize_t
readether(struct iodesc *d, void **pkt, void **payload, time_t tleft,
    uint16_t *etype)
{
	ssize_t n;
	struct ether_header *eh;
	void *ptr;

#ifdef ETHER_DEBUG
 	if (debug)
		printf("readether: called\n");
#endif

	ptr = NULL;
	n = netif_get(d, &ptr, tleft);
	if (n == -1 || n < sizeof(*eh)) {
		free(ptr);
		return (-1);
	}

	eh = (struct ether_header *)((uintptr_t)ptr + ETHER_ALIGN);
	/* Validate Ethernet address. */
	if (bcmp(d->myea, eh->ether_dhost, 6) != 0 &&
	    bcmp(bcea, eh->ether_dhost, 6) != 0) {
#ifdef ETHER_DEBUG
		if (debug)
			printf("readether: not ours (ea=%s)\n",
			    ether_sprintf(eh->ether_dhost));
#endif
		free(ptr);
		return (-1);
	}

	*pkt = ptr;
	*payload = (void *)((uintptr_t)eh + sizeof(*eh));
	*etype = ntohs(eh->ether_type);

	n -= sizeof(*eh);
	return (n);
}
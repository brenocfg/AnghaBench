#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {struct sockaddr* next; struct sockaddr* dstaddr; struct sockaddr* addr; struct sockaddr* netmask; struct sockaddr* broadaddr; } ;
struct TYPE_3__ {struct sockaddr* addresses; } ;
typedef  TYPE_1__ pcap_if_t ;
typedef  struct sockaddr pcap_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 scalar_t__ dup_sockaddr (struct sockaddr*,size_t) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct sockaddr*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int
add_addr_to_dev(pcap_if_t *curdev,
    struct sockaddr *addr, size_t addr_size,
    struct sockaddr *netmask, size_t netmask_size,
    struct sockaddr *broadaddr, size_t broadaddr_size,
    struct sockaddr *dstaddr, size_t dstaddr_size,
    char *errbuf)
{
	pcap_addr_t *curaddr, *prevaddr, *nextaddr;

	/*
	 * Allocate the new entry and fill it in.
	 */
	curaddr = (pcap_addr_t *)malloc(sizeof(pcap_addr_t));
	if (curaddr == NULL) {
		pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
		    errno, "malloc");
		return (-1);
	}

	curaddr->next = NULL;
	if (addr != NULL && addr_size != 0) {
		curaddr->addr = (struct sockaddr *)dup_sockaddr(addr, addr_size);
		if (curaddr->addr == NULL) {
			pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
			    errno, "malloc");
			free(curaddr);
			return (-1);
		}
	} else
		curaddr->addr = NULL;

	if (netmask != NULL && netmask_size != 0) {
		curaddr->netmask = (struct sockaddr *)dup_sockaddr(netmask, netmask_size);
		if (curaddr->netmask == NULL) {
			pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
			    errno, "malloc");
			if (curaddr->addr != NULL)
				free(curaddr->addr);
			free(curaddr);
			return (-1);
		}
	} else
		curaddr->netmask = NULL;

	if (broadaddr != NULL && broadaddr_size != 0) {
		curaddr->broadaddr = (struct sockaddr *)dup_sockaddr(broadaddr, broadaddr_size);
		if (curaddr->broadaddr == NULL) {
			pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
			    errno, "malloc");
			if (curaddr->netmask != NULL)
				free(curaddr->netmask);
			if (curaddr->addr != NULL)
				free(curaddr->addr);
			free(curaddr);
			return (-1);
		}
	} else
		curaddr->broadaddr = NULL;

	if (dstaddr != NULL && dstaddr_size != 0) {
		curaddr->dstaddr = (struct sockaddr *)dup_sockaddr(dstaddr, dstaddr_size);
		if (curaddr->dstaddr == NULL) {
			pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
			    errno, "malloc");
			if (curaddr->broadaddr != NULL)
				free(curaddr->broadaddr);
			if (curaddr->netmask != NULL)
				free(curaddr->netmask);
			if (curaddr->addr != NULL)
				free(curaddr->addr);
			free(curaddr);
			return (-1);
		}
	} else
		curaddr->dstaddr = NULL;

	/*
	 * Find the end of the list of addresses.
	 */
	for (prevaddr = curdev->addresses; prevaddr != NULL; prevaddr = nextaddr) {
		nextaddr = prevaddr->next;
		if (nextaddr == NULL) {
			/*
			 * This is the end of the list.
			 */
			break;
		}
	}

	if (prevaddr == NULL) {
		/*
		 * The list was empty; this is the first member.
		 */
		curdev->addresses = curaddr;
	} else {
		/*
		 * "prevaddr" is the last member of the list; append
		 * this member to it.
		 */
		prevaddr->next = curaddr;
	}

	return (0);
}
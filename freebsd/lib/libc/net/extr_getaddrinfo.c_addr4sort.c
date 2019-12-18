#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; } ;
struct addrinfo {struct addrinfo* ai_next; scalar_t__ ai_addr; } ;
struct addr_ptr {int aval; struct addrinfo* ai; } ;
typedef  TYPE_4__* res_state ;
struct TYPE_9__ {unsigned int nsort; TYPE_3__* sort_list; } ;
struct TYPE_6__ {int s_addr; } ;
struct TYPE_8__ {int mask; TYPE_1__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct addr_ptr*) ; 
 struct addr_ptr* malloc (int) ; 

__attribute__((used)) static int
addr4sort(struct addrinfo *sentinel, res_state res)
{
	struct addrinfo *ai;
	struct addr_ptr *addrs, addr;
	struct sockaddr_in *sin;
	int naddrs, i, j;
	int needsort = 0;

	if (!sentinel)
		return -1;
	naddrs = 0;
	for (ai = sentinel->ai_next; ai; ai = ai->ai_next)
		naddrs++;
	if (naddrs < 2)
		return 0;		/* We don't need sorting. */
	if ((addrs = malloc(sizeof(struct addr_ptr) * naddrs)) == NULL)
		return -1;
	i = 0;
	for (ai = sentinel->ai_next; ai; ai = ai->ai_next) {
		sin = (struct sockaddr_in *)ai->ai_addr;
		for (j = 0; (unsigned)j < res->nsort; j++) {
			if (res->sort_list[j].addr.s_addr ==
			    (sin->sin_addr.s_addr & res->sort_list[j].mask))
				break;
		}
		addrs[i].ai = ai;
		addrs[i].aval = j;
		if (needsort == 0 && i > 0 && j < addrs[i - 1].aval)
			needsort = i;
		i++;
	}
	if (!needsort) {
		free(addrs);
		return 0;
	}

	while (needsort < naddrs) {
		for (j = needsort - 1; j >= 0; j--) {
			if (addrs[j].aval > addrs[j+1].aval) {
				addr = addrs[j];
				addrs[j] = addrs[j + 1];
				addrs[j + 1] = addr;
			} else
				break;
		}
		needsort++;
	}

	ai = sentinel;
	for (i = 0; i < naddrs; ++i) {
		ai->ai_next = addrs[i].ai;
		ai = ai->ai_next;
	}
	ai->ai_next = NULL;
	free(addrs);
	return 0;
}
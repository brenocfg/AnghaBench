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
struct TYPE_4__ {int* sockets; int /*<<< orphan*/  ifap; } ;
typedef  TYPE_1__ ifconfig_handle_t ;

/* Variables and functions */
 int AF_MAX ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  freeifaddrs (int /*<<< orphan*/ ) ; 

void
ifconfig_close(ifconfig_handle_t *h)
{

	for (int i = 0; i <= AF_MAX; i++) {
		if (h->sockets[i] != -1) {
			(void)close(h->sockets[i]);
		}
	}
	freeifaddrs(h->ifap);
	free(h);
}
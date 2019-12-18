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
struct netif {int dummy; } ;
struct TYPE_2__ {struct netif* io_netif; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int SOPEN_MAX ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  netif_detach (struct netif*) ; 
 TYPE_1__* sockets ; 

int
netif_close(int sock)
{
	if (sock >= SOPEN_MAX) {
		errno = EBADF;
		return (-1);
	}
	netif_detach(sockets[sock].io_netif);
	sockets[sock].io_netif = (struct netif *)0;

	return (0);
}
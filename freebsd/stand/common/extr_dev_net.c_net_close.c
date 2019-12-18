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
struct open_file {int /*<<< orphan*/ * f_devdata; } ;

/* Variables and functions */
 scalar_t__ debug ; 
 int netdev_opens ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
net_close(struct open_file *f)
{

#ifdef	NETIF_DEBUG
	if (debug)
		printf("net_close: opens=%d\n", netdev_opens);
#endif

	f->f_devdata = NULL;

	return (0);
}
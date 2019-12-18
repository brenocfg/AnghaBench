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
typedef  int u_int ;
struct sockaddr_dl {int dummy; } ;

/* Variables and functions */
 unsigned char* LLADDR (struct sockaddr_dl*) ; 

__attribute__((used)) static u_int
al_count_maddr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	unsigned char *mac;

	mac = LLADDR(sdl);
	/* default mc address inside mac address */
	if (mac[3] != 0 && mac[4] != 0 && mac[5] != 1)
		return (1);
	else
		return (0);
}
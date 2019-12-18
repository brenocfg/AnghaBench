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
struct ether_addr {int* octet; } ;

/* Variables and functions */
 int sscanf (char const*,char*,int*,int*,int*,int*,int*,int*,char*) ; 

int
ether_line(const char *l, struct ether_addr *e, char *hostname)
{
	int i, o[6];

	i = sscanf(l, "%x:%x:%x:%x:%x:%x %s", &o[0], &o[1], &o[2], &o[3],
	    &o[4], &o[5], hostname);
	if (i == 7) {
		for (i = 0; i < 6; i++)
			e->octet[i] = o[i];
		return (0);
	} else {
		return (-1);
	}
}
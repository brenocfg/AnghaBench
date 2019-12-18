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
 int sprintf (char*,char*,int,int,int,int,int,int) ; 

char *
ether_ntoa_r(const struct ether_addr *n, char *a)
{
	int i;

	i = sprintf(a, "%02x:%02x:%02x:%02x:%02x:%02x", n->octet[0],
	    n->octet[1], n->octet[2], n->octet[3], n->octet[4], n->octet[5]);
	if (i < 17)
		return (NULL);
	return (a);
}
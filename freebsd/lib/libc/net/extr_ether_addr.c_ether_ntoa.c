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
struct ether_addr {int dummy; } ;

/* Variables and functions */
 char* ether_ntoa_r (struct ether_addr const*,char*) ; 

char *
ether_ntoa(const struct ether_addr *n)
{
	static char a[18];

	return (ether_ntoa_r(n, a));
}
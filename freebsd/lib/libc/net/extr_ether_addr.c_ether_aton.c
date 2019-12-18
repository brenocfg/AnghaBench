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
 struct ether_addr* ether_aton_r (char const*,struct ether_addr*) ; 

struct ether_addr *
ether_aton(const char *a)
{
	static struct ether_addr e;

	return (ether_aton_r(a, &e));
}
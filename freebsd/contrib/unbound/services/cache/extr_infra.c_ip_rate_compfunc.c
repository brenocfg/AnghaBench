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
struct ip_rate_key {int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int sockaddr_cmp_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ip_rate_compfunc(void* key1, void* key2)
{
	struct ip_rate_key* k1 = (struct ip_rate_key*)key1;
	struct ip_rate_key* k2 = (struct ip_rate_key*)key2;
	return sockaddr_cmp_addr(&k1->addr, k1->addrlen,
		&k2->addr, k2->addrlen);
}
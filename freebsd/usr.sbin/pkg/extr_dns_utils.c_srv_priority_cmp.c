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
struct dns_srvinfo {unsigned int priority; } ;

/* Variables and functions */

__attribute__((used)) static int
srv_priority_cmp(const void *a, const void *b)
{
	const struct dns_srvinfo *da, *db;
	unsigned int r, l;

	da = *(struct dns_srvinfo * const *)a;
	db = *(struct dns_srvinfo * const *)b;

	l = da->priority;
	r = db->priority;

	return ((l > r) - (l < r));
}
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
struct dns_srvinfo {unsigned int priority; unsigned int finalweight; } ;

/* Variables and functions */

__attribute__((used)) static int
srv_final_cmp(const void *a, const void *b)
{
	const struct dns_srvinfo *da, *db;
	unsigned int r, l, wr, wl;
	int res;

	da = *(struct dns_srvinfo * const *)a;
	db = *(struct dns_srvinfo * const *)b;

	l = da->priority;
	r = db->priority;

	res = ((l > r) - (l < r));

	if (res == 0) {
		wl = da->finalweight;
		wr = db->finalweight;
		res = ((wr > wl) - (wr < wl));
	}

	return (res);
}
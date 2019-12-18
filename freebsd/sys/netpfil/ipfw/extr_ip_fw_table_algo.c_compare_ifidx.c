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
typedef  scalar_t__ uint16_t ;
struct ifidx {scalar_t__ kidx; } ;

/* Variables and functions */

int
compare_ifidx(const void *k, const void *v)
{
	const struct ifidx *ifidx;
	uint16_t key;

	key = *((const uint16_t *)k);
	ifidx = (const struct ifidx *)v;

	if (key < ifidx->kidx)
		return (-1);
	else if (key > ifidx->kidx)
		return (1);

	return (0);
}
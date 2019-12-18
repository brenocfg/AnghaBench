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
struct g_provider {scalar_t__ ace; scalar_t__ acw; scalar_t__ acr; } ;

/* Variables and functions */

int
gv_provider_is_open(struct g_provider *pp)
{
	if (pp == NULL)
		return (0);

	if (pp->acr || pp->acw || pp->ace)
		return (1);

	return (0);
}
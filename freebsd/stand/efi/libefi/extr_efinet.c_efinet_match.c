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
struct netif {scalar_t__ nif_unit; } ;
struct devdesc {scalar_t__ d_unit; } ;

/* Variables and functions */

__attribute__((used)) static int
efinet_match(struct netif *nif, void *machdep_hint)
{
	struct devdesc *dev = machdep_hint;

	if (dev->d_unit == nif->nif_unit)
		return (1);
	return(0);
}
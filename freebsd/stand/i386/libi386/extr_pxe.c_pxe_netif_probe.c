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
struct netif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * pxe_call ; 

__attribute__((used)) static int
pxe_netif_probe(struct netif *nif, void *machdep_hint)
{
	if (pxe_call == NULL)
		return (-1);

	return (0);
}
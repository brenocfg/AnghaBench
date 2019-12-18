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
typedef  int /*<<< orphan*/  t_Error ;
struct resource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  powerpc_intr_mask (uintptr_t) ; 
 uintptr_t rman_get_start (struct resource*) ; 

t_Error
XX_DisableIntr(uintptr_t irq)
{
	struct resource *r;

	r = (struct resource *)irq;
	irq = rman_get_start(r);

	powerpc_intr_mask(irq);

	return (E_OK);
}
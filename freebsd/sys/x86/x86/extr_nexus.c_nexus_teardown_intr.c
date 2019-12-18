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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int intr_remove_handler (void*) ; 
 int /*<<< orphan*/  rman_set_irq_cookie (struct resource*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nexus_teardown_intr(device_t dev, device_t child, struct resource *r, void *ih)
{
	int error;

	error = intr_remove_handler(ih);
	if (error == 0)
		rman_set_irq_cookie(r, NULL);
	return (error);
}
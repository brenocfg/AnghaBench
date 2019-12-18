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
struct gpiobus_ivar {scalar_t__ npins; int /*<<< orphan*/ * pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
gpiobus_free_ivars(struct gpiobus_ivar *devi)
{

	if (devi->pins) {
		free(devi->pins, M_DEVBUF);
		devi->pins = NULL;
	}
	devi->npins = 0;
}
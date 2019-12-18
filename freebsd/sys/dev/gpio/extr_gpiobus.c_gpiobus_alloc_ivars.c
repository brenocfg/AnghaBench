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
typedef  int /*<<< orphan*/  uint32_t ;
struct gpiobus_ivar {int npins; int /*<<< orphan*/ * pins; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 

int
gpiobus_alloc_ivars(struct gpiobus_ivar *devi)
{

	/* Allocate pins and flags memory. */
	devi->pins = malloc(sizeof(uint32_t) * devi->npins, M_DEVBUF,
	    M_NOWAIT | M_ZERO);
	if (devi->pins == NULL)
		return (ENOMEM);
	return (0);
}
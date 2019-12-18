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
struct acpi_intr {scalar_t__ (* ai_handler ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  ai_context; } ;

/* Variables and functions */
 scalar_t__ ACPI_INTERRUPT_HANDLED ; 
 int FILTER_HANDLED ; 
 int FILTER_STRAY ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_intr_handler(void *arg)
{
	struct acpi_intr *ai;

	ai = arg;
	KASSERT(ai != NULL && ai->ai_handler != NULL,
	    ("invalid ACPI interrupt handler"));
	if (ai->ai_handler(ai->ai_context) == ACPI_INTERRUPT_HANDLED)
		return (FILTER_HANDLED);
	return (FILTER_STRAY);
}
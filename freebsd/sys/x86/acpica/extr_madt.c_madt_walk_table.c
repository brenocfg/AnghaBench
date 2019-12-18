#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  acpi_subtable_handler ;
struct TYPE_4__ {int Length; } ;
struct TYPE_5__ {TYPE_1__ Header; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_walk_subtables (TYPE_2__*,char*,int /*<<< orphan*/ *,void*) ; 
 TYPE_2__* madt ; 

__attribute__((used)) static void
madt_walk_table(acpi_subtable_handler *handler, void *arg)
{

	acpi_walk_subtables(madt + 1, (char *)madt + madt->Header.Length,
	    handler, arg);
}
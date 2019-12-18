#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ usages; } ;

/* Variables and functions */
 TYPE_1__ acpi_aml_io ; 

__attribute__((used)) static inline bool __acpi_aml_used(void)
{
	return acpi_aml_io.usages ? true : false;
}
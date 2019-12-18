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
struct circ_buf {int dummy; } ;
struct TYPE_2__ {unsigned long flags; } ;

/* Variables and functions */
 TYPE_1__ acpi_aml_io ; 
 scalar_t__ circ_space (struct circ_buf*) ; 

__attribute__((used)) static inline bool __acpi_aml_writable(struct circ_buf *circ, unsigned long flag)
{
	/*
	 * Another write is not in progress and there is buffer space
	 * available for write.
	 */
	if (!(acpi_aml_io.flags & flag) && circ_space(circ))
		return true;
	return false;
}
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
struct ioapic_intsrc {scalar_t__ io_vector; } ;
struct intsrc {int dummy; } ;

/* Variables and functions */
 int lapic_intr_pending (scalar_t__) ; 

__attribute__((used)) static int
ioapic_source_pending(struct intsrc *isrc)
{
	struct ioapic_intsrc *intpin = (struct ioapic_intsrc *)isrc;

	if (intpin->io_vector == 0)
		return 0;
	return (lapic_intr_pending(intpin->io_vector));
}
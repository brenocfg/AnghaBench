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

/* Variables and functions */
 int IRQ_PEND_IO_ISC_0 ; 

__attribute__((used)) static inline int isc_to_irq_type(unsigned long isc)
{
	return IRQ_PEND_IO_ISC_0 - isc;
}
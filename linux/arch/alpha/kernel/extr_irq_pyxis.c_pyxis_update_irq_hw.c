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
typedef  unsigned long* vulp ;

/* Variables and functions */
 scalar_t__ PYXIS_INT_MASK ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static inline void
pyxis_update_irq_hw(unsigned long mask)
{
	*(vulp)PYXIS_INT_MASK = mask;
	mb();
	*(vulp)PYXIS_INT_MASK;
}
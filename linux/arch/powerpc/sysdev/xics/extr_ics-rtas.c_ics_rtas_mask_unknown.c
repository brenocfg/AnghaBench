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
struct ics {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ics_rtas_mask_real_irq (unsigned long) ; 

__attribute__((used)) static void ics_rtas_mask_unknown(struct ics *ics, unsigned long vec)
{
	ics_rtas_mask_real_irq(vec);
}
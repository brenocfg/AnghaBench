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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  XX_INTR_FLAG_FMAN_FIX ; 
 TYPE_1__* XX_IntrInfo ; 

void
XX_FmanFixIntr(int irq)
{

	XX_IntrInfo[irq].flags |= XX_INTR_FLAG_FMAN_FIX;
}
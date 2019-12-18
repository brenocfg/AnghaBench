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
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;

/* Variables and functions */
 int INTR_POLARITY_CONFORM ; 
 int INTR_TRIGGER_CONFORM ; 
 int fdt32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fdt_intc_decode_ic(phandle_t node, pcell_t *intr, int *interrupt, int *trig,
    int *pol)
{

	*interrupt = fdt32_to_cpu(intr[0]);
	*trig = INTR_TRIGGER_CONFORM;
	*pol = INTR_POLARITY_CONFORM;

	return (0);
}
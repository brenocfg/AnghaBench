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
 int ENXIO ; 
 int INTR_POLARITY_HIGH ; 
 int INTR_TRIGGER_EDGE ; 
 int fdt32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_is_compatible_strict (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
fdt_pic_decode_ic(phandle_t node, pcell_t *intr, int *interrupt, int *trig,
    int *pol)
{

	/*
	 * The single core chips have just an Amlogic PIC.
	 */
	if (!fdt_is_compatible_strict(node, "amlogic,aml8726-pic"))
		return (ENXIO);

	*interrupt = fdt32_to_cpu(intr[1]);
	*trig = INTR_TRIGGER_EDGE;
	*pol = INTR_POLARITY_HIGH;

	return (0);
}
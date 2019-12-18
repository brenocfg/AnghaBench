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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_buffer_printf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
loc_cm_print(ldns_buffer *output, uint8_t mantissa, uint8_t exponent)
{
	uint8_t i;
	/* is it 0.<two digits> ? */
	if(exponent < 2) {
		if(exponent == 1)
			mantissa *= 10;
		ldns_buffer_printf(output, "0.%02ld", (long)mantissa);
		return;
	}
	/* always <digit><string of zeros> */
	ldns_buffer_printf(output, "%d", (int)mantissa);
	for(i=0; i<exponent-2; i++)
		ldns_buffer_printf(output, "0");
}
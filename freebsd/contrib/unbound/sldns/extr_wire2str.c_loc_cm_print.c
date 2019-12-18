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

/* Variables and functions */
 int sldns_str_print (char**,size_t*,char*,...) ; 

__attribute__((used)) static int
loc_cm_print(char** str, size_t* sl, uint8_t mantissa, uint8_t exponent)
{
	int w = 0;
	uint8_t i;
	/* is it 0.<two digits> ? */
	if(exponent < 2) {
		if(exponent == 1)
			mantissa *= 10;
		return sldns_str_print(str, sl, "0.%02ld", (long)mantissa);
	}
	/* always <digit><string of zeros> */
	w += sldns_str_print(str, sl, "%d", (int)mantissa);
	for(i=0; i<exponent-2; i++)
		w += sldns_str_print(str, sl, "0");
	return w;
}
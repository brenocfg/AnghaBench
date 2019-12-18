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
typedef  int /*<<< orphan*/  val ;

/* Variables and functions */
 scalar_t__ random_get_bytes (unsigned char*,int) ; 
 unsigned int wps_pin_checksum (unsigned int) ; 

int wps_generate_pin(unsigned int *pin)
{
	unsigned int val;

	/* Generate seven random digits for the PIN */
	if (random_get_bytes((unsigned char *) &val, sizeof(val)) < 0)
		return -1;
	val %= 10000000;

	/* Append checksum digit */
	*pin = val * 10 + wps_pin_checksum(val);
	return 0;
}
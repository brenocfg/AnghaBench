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
typedef  int u_int8_t ;

/* Variables and functions */
 int* poweroften ; 
 char* precsize_ntoa_retbuf ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long,unsigned long) ; 

__attribute__((used)) static const char *
precsize_ntoa(u_int8_t prec)
{
	char *retbuf = precsize_ntoa_retbuf;
	unsigned long val;
	int mantissa, exponent;

	mantissa = (int)((prec >> 4) & 0x0f) % 10;
	exponent = (int)((prec >> 0) & 0x0f) % 10;

	val = mantissa * poweroften[exponent];

	(void) sprintf(retbuf, "%lu.%.2lu", val/100, val%100);
	return (retbuf);
}
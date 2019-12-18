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
 int /*<<< orphan*/  snprintf (char*,size_t,char*,double) ; 

__attribute__((used)) static void
convert_sff_voltage(char *buf, size_t size, uint8_t *xbuf)
{
	double d;

	d = (double)((xbuf[0] << 8) | xbuf[1]);
	snprintf(buf, size, "%.2f Volts", d / 10000);
}
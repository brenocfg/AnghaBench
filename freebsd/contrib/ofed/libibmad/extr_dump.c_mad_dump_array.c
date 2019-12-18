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
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void mad_dump_array(char *buf, int bufsz, void *val, int valsz)
{
	uint8_t *p = val, *e;
	char *s = buf;

	if (bufsz < valsz * 2)
		valsz = bufsz / 2;

	for (p = val, e = p + valsz; p < e; p++, s += 2)
		sprintf(s, "%02x", *p);
}
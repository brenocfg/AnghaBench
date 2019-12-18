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
typedef  int /*<<< orphan*/  units ;
typedef  int u_int ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,double,char*) ; 

__attribute__((used)) static const char *
norm2(char *buf, double val, char *fmt, int normalize)
{
	char *units[] = { "", "K", "M", "G", "T" };
	u_int i;
	if (normalize)
		for (i = 0; val >=1000 && i < sizeof(units)/sizeof(char *) - 1; i++)
			val /= 1000;
	else
		i=0;
	sprintf(buf, fmt, val, units[i]);
	return buf;
}
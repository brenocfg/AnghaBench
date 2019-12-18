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
typedef  int u_char ;
typedef  int /*<<< orphan*/  s1 ;

/* Variables and functions */
 int FI ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,double) ; 

__attribute__((used)) static void
doublefreq(			/* returns void */
	double freq,		/* frequency */
	u_char *x,		/* radio frequency */
	int len			/* length (octets) */
	)
{
	int i;
	char s1[16];
	char *y;

	snprintf(s1, sizeof(s1), " %10.0f", freq);
	y = s1 + 10;
	i = 0;
	while (*y != ' ') {
		x[i] = *y-- & 0x0f;
		x[i] = x[i] | ((*y-- & 0x0f) << 4);
		i++;
	}
	for ( ; i < len; i++)
		x[i] = 0;
	x[i] = FI;
}
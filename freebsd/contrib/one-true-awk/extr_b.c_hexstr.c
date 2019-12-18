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
typedef  int uschar ;

/* Variables and functions */
 scalar_t__ isdigit (int) ; 
 scalar_t__ isxdigit (int) ; 

int hexstr(uschar **pp)	/* find and eval hex string at pp, return new p */
{			/* only pick up one 8-bit byte (2 chars) */
	uschar *p;
	int n = 0;
	int i;

	for (i = 0, p = (uschar *) *pp; i < 2 && isxdigit(*p); i++, p++) {
		if (isdigit(*p))
			n = 16 * n + *p - '0';
		else if (*p >= 'a' && *p <= 'f')
			n = 16 * n + *p - 'a' + 10;
		else if (*p >= 'A' && *p <= 'F')
			n = 16 * n + *p - 'A' + 10;
	}
	*pp = (uschar *) p;
	return n;
}
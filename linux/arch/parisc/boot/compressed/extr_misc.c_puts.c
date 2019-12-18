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

/* Variables and functions */
 int /*<<< orphan*/  pdc_iodc_print (char const*,int) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 

int puts(const char *s)
{
	const char *nuline = s;

	while ((nuline = strchr(s, '\n')) != NULL) {
		if (nuline != s)
			pdc_iodc_print(s, nuline - s);
		pdc_iodc_print("\r\n", 2);
		s = nuline + 1;
	}
	if (*s != '\0')
		pdc_iodc_print(s, strlen(s));

	return 0;
}
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
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 

__attribute__((used)) static void
convert_sff_name(char *buf, size_t size, char *xbuf)
{
	char *p;

	for (p = &xbuf[16]; *(p - 1) == 0x20; p--)
		;
	*p = '\0';
	snprintf(buf, size, "%s", xbuf);
}
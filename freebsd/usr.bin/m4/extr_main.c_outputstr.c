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
 int /*<<< orphan*/  CHRSAVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reallyoutputstr (char const*) ; 
 scalar_t__ sp ; 

void
outputstr(const char *s)
{
	if (sp < 0)
		reallyoutputstr(s);
	else
		while (*s)
			CHRSAVE(*s++);
}
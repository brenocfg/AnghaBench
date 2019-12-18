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
 int /*<<< orphan*/ * m4wraps ; 
 int maxwraps ; 
 int wrapindex ; 
 int /*<<< orphan*/ * xreallocarray (int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static void
dom4wrap(const char *text)
{
	if (wrapindex >= maxwraps) {
		if (maxwraps == 0)
			maxwraps = 16;
		else
			maxwraps *= 2;
		m4wraps = xreallocarray(m4wraps, maxwraps, sizeof(*m4wraps),
		   "too many m4wraps");
	}
	m4wraps[wrapindex++] = xstrdup(text);
}
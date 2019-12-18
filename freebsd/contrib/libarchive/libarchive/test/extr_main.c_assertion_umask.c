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
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 int /*<<< orphan*/  umask (int) ; 

int
assertion_umask(const char *file, int line, int mask)
{
	assertion_count(file, line);
	(void)file; /* UNUSED */
	(void)line; /* UNUSED */
	umask(mask);
	return (1);
}
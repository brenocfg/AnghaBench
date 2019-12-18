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
 int assertion_file_time (char const*,int,char const*,long,long,char,int /*<<< orphan*/ ) ; 

int
assertion_file_birthtime(const char *file, int line,
    const char *pathname, long t, long nsec)
{
	return assertion_file_time(file, line, pathname, t, nsec, 'b', 0);
}
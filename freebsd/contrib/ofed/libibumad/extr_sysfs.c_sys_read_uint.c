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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 unsigned int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sys_read_string (char const*,char const*,char*,int) ; 

int sys_read_uint(const char *dir_name, const char *file_name, unsigned *u)
{
	char buf[32];
	int r;

	if ((r = sys_read_string(dir_name, file_name, buf, sizeof(buf))) < 0)
		return r;

	*u = strtoul(buf, NULL, 0);

	return 0;
}
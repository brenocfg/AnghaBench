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
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int stat (char const*,struct stat*) ; 

int
is_nonempty_file(const char *pathname)
{
	struct stat buf;

	if (stat(pathname, &buf) == -1)
		return 0;

	return S_ISREG(buf.st_mode) && buf.st_size > 0;
}
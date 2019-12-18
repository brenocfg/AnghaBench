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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 

FILE *xfopen(const char *path, const char *mode)
{
	for (;;) {
		FILE *fp = fopen(path, mode);
		if (fp)
			return fp;
		if (errno == EINTR)
			continue;

		if (*mode && mode[1] == '+')
			die_errno(_("could not open '%s' for reading and writing"), path);
		else if (*mode == 'w' || *mode == 'a')
			die_errno(_("could not open '%s' for writing"), path);
		else
			die_errno(_("could not open '%s' for reading"), path);
	}
}
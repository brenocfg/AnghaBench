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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTDIR ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * realpath (char const*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 

int
checkpath(const char *path, char *resolved)
{
	struct stat sb;

	if (realpath(path, resolved) == NULL || stat(resolved, &sb) != 0)
		return (1);
	if (!S_ISDIR(sb.st_mode)) {
		errno = ENOTDIR;
		return (1);
	}
	return (0);
}
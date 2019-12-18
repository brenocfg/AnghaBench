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
 int /*<<< orphan*/  EISDIR ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int unlink (char*) ; 

int
rm(char *name)
{
	struct stat sb;

	if (stat(name, &sb) < 0)
		return (-1);
	if (!S_ISREG(sb.st_mode)) {
		errno = EISDIR;
		return (-1);
	}
	return (unlink(name));
}
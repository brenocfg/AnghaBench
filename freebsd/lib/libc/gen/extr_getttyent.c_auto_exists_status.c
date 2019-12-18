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
struct stat {int dummy; } ;

/* Variables and functions */
 int TTY_IFEXISTS ; 
 int TTY_ON ; 
 int /*<<< orphan*/  asprintf (char**,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 

__attribute__((used)) static int
auto_exists_status(const char *ty_name)
{
	struct stat sb;
	char *dev;
	int rv;

	rv = TTY_IFEXISTS;
	if (*ty_name == '/')
		asprintf(&dev, "%s", ty_name);
	else
		asprintf(&dev, "/dev/%s", ty_name);
	if (dev != NULL && stat(dev, &sb) == 0)
		rv |= TTY_ON;
	free(dev);
	return (rv);
}
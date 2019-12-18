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
 int /*<<< orphan*/ * mountprog ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int
use_mountprog(const char *vfstype)
{
	/* XXX: We need to get away from implementing external mount
	 *      programs for every filesystem, and move towards having
	 *	each filesystem properly implement the nmount() system call.
	 */
	unsigned int i;
	const char *fs[] = {
	"cd9660", "mfs", "msdosfs", "nfs",
	"nullfs", "smbfs", "udf", "unionfs",
	NULL
	};

	if (mountprog != NULL)
		return (1);

	for (i = 0; fs[i] != NULL; ++i) {
		if (strcmp(vfstype, fs[i]) == 0)
			return (1);
	}

	return (0);
}
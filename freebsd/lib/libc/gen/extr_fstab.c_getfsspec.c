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
struct fstab {int /*<<< orphan*/  fs_spec; } ;

/* Variables and functions */
 struct fstab _fs_fstab ; 
 scalar_t__ fstabscan () ; 
 scalar_t__ setfsent () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

struct fstab *
getfsspec(const char *name)
{

	if (setfsent())
		while (fstabscan())
			if (!strcmp(_fs_fstab.fs_spec, name))
				return (&_fs_fstab);
	return (NULL);
}
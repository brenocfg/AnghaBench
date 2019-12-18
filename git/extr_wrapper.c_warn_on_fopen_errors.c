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
 scalar_t__ ENOENT ; 
 scalar_t__ ENOTDIR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  warn_on_inaccessible (char const*) ; 

int warn_on_fopen_errors(const char *path)
{
	if (errno != ENOENT && errno != ENOTDIR) {
		warn_on_inaccessible(path);
		return -1;
	}

	return 0;
}
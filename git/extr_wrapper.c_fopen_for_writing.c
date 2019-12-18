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
 scalar_t__ EPERM ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  unlink (char const*) ; 

FILE *fopen_for_writing(const char *path)
{
	FILE *ret = fopen(path, "w");

	if (!ret && errno == EPERM) {
		if (!unlink(path))
			ret = fopen(path, "w");
		else
			errno = EPERM;
	}
	return ret;
}
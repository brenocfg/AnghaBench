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
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 int /*<<< orphan*/  warn_on_fopen_errors (char const*) ; 

FILE *fopen_or_warn(const char *path, const char *mode)
{
	FILE *fp = fopen(path, mode);

	if (fp)
		return fp;

	warn_on_fopen_errors(path);
	return NULL;
}
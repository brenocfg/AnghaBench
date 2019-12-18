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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EISDIR ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 

FILE *
pfctl_fopen(const char *name, const char *mode)
{
	struct stat	 st;
	FILE		*fp;

	fp = fopen(name, mode);
	if (fp == NULL)
		return (NULL);
	if (fstat(fileno(fp), &st)) {
		fclose(fp);
		return (NULL);
	}
	if (S_ISDIR(st.st_mode)) {
		fclose(fp);
		errno = EISDIR;
		return (NULL);
	}
	return (fp);
}
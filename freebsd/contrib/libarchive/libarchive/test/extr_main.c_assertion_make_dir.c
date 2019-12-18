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
 scalar_t__ _mkdir (char const*) ; 
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 int /*<<< orphan*/  assertion_file_mode (char const*,int,char const*,int) ; 
 scalar_t__ chmod (char const*,int) ; 
 int /*<<< orphan*/  failure_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,char const*) ; 
 scalar_t__ mkdir (char const*,int) ; 

int
assertion_make_dir(const char *file, int line, const char *dirname, int mode)
{
	assertion_count(file, line);
#if defined(_WIN32) && !defined(__CYGWIN__)
	(void)mode; /* UNUSED */
	if (0 == _mkdir(dirname))
		return (1);
#else
	if (0 == mkdir(dirname, mode)) {
		if (0 == chmod(dirname, mode)) {
			assertion_file_mode(file, line, dirname, mode);
			return (1);
		}
	}
#endif
	failure_start(file, line, "Could not create directory %s", dirname);
	failure_finish(NULL);
	return(0);
}
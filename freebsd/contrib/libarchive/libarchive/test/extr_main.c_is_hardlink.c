#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_ino; scalar_t__ st_dev; } ;
struct TYPE_3__ {scalar_t__ dwVolumeSerialNumber; scalar_t__ nFileIndexHigh; scalar_t__ nFileIndexLow; } ;
typedef  TYPE_1__ BY_HANDLE_FILE_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 int /*<<< orphan*/  failure_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,char const*) ; 
 int lstat (char const*,struct stat*) ; 
 int my_GetFileInformationByName (char const*,TYPE_1__*) ; 

__attribute__((used)) static int
is_hardlink(const char *file, int line,
    const char *path1, const char *path2)
{
#if defined(_WIN32) && !defined(__CYGWIN__)
	BY_HANDLE_FILE_INFORMATION bhfi1, bhfi2;
	int r;

	assertion_count(file, line);
	r = my_GetFileInformationByName(path1, &bhfi1);
	if (r == 0) {
		failure_start(file, line, "File %s can't be inspected?", path1);
		failure_finish(NULL);
		return (0);
	}
	r = my_GetFileInformationByName(path2, &bhfi2);
	if (r == 0) {
		failure_start(file, line, "File %s can't be inspected?", path2);
		failure_finish(NULL);
		return (0);
	}
	return (bhfi1.dwVolumeSerialNumber == bhfi2.dwVolumeSerialNumber
		&& bhfi1.nFileIndexHigh == bhfi2.nFileIndexHigh
		&& bhfi1.nFileIndexLow == bhfi2.nFileIndexLow);
#else
	struct stat st1, st2;
	int r;

	assertion_count(file, line);
	r = lstat(path1, &st1);
	if (r != 0) {
		failure_start(file, line, "File should exist: %s", path1);
		failure_finish(NULL);
		return (0);
	}
	r = lstat(path2, &st2);
	if (r != 0) {
		failure_start(file, line, "File should exist: %s", path2);
		failure_finish(NULL);
		return (0);
	}
	return (st1.st_ino == st2.st_ino && st1.st_dev == st2.st_dev);
#endif
}
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
struct stat {scalar_t__ st_ino; } ;
typedef  int int64_t ;
struct TYPE_3__ {int nFileIndexHigh; } ;
typedef  TYPE_1__ BY_HANDLE_FILE_INFORMATION ;

/* Variables and functions */
 int my_GetFileInformationByName (char const*,TYPE_1__*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

int
is_LargeInode(const char *file)
{
#if defined(_WIN32) && !defined(__CYGWIN__)
	BY_HANDLE_FILE_INFORMATION bhfi;
	int r;

	r = my_GetFileInformationByName(file, &bhfi);
	if (r != 0)
		return (0);
	return (bhfi.nFileIndexHigh & 0x0000FFFFUL);
#else
	struct stat st;
	int64_t ino;

	if (stat(file, &st) < 0)
		return (0);
	ino = (int64_t)st.st_ino;
	return (ino > 0xffffffff);
#endif
}
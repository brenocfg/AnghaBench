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
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  BY_HANDLE_FILE_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  GetFileInformationByHandle (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  _get_osfhandle (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  git_win32__file_information_to_stat (struct stat*,int /*<<< orphan*/ *) ; 

int p_fstat(int fd, struct stat *buf)
{
	BY_HANDLE_FILE_INFORMATION fhInfo;

	HANDLE fh = (HANDLE)_get_osfhandle(fd);

	if (fh == INVALID_HANDLE_VALUE ||
		!GetFileInformationByHandle(fh, &fhInfo)) {
		errno = EBADF;
		return -1;
	}

	git_win32__file_information_to_stat(buf, &fhInfo);
	return 0;
}
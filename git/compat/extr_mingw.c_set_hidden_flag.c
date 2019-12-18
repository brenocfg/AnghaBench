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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int DWORD ;

/* Variables and functions */
 int FILE_ATTRIBUTE_HIDDEN ; 
 int GetFileAttributesW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ SetFileAttributesW (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  err_win_to_posix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static int set_hidden_flag(const wchar_t *path, int set)
{
	DWORD original = GetFileAttributesW(path), modified;
	if (set)
		modified = original | FILE_ATTRIBUTE_HIDDEN;
	else
		modified = original & ~FILE_ATTRIBUTE_HIDDEN;
	if (original == modified || SetFileAttributesW(path, modified))
		return 0;
	errno = err_win_to_posix(GetLastError());
	return -1;
}
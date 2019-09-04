#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_11__ {int /*<<< orphan*/  ptr; scalar_t__ size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_PATH_LIST_SEPARATOR ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  REG_MSYSGIT_INSTALL ; 
 int /*<<< orphan*/  REG_MSYSGIT_INSTALL_LOCAL ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_join (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git_buf_oom (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_set (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  win32_find_git_in_path (TYPE_1__*,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  win32_find_git_in_registry (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

int git_win32__find_system_dirs(git_buf *out, const wchar_t *subdir)
{
	git_buf buf = GIT_BUF_INIT;

	/* directories where git.exe & git.cmd are found */
	if (!win32_find_git_in_path(&buf, L"git.exe", subdir) && buf.size)
		git_buf_set(out, buf.ptr, buf.size);
	else
		git_buf_clear(out);

	if (!win32_find_git_in_path(&buf, L"git.cmd", subdir) && buf.size)
		git_buf_join(out, GIT_PATH_LIST_SEPARATOR, out->ptr, buf.ptr);

	/* directories where git is installed according to registry */
	if (!win32_find_git_in_registry(
			&buf, HKEY_CURRENT_USER, REG_MSYSGIT_INSTALL_LOCAL, subdir) && buf.size)
		git_buf_join(out, GIT_PATH_LIST_SEPARATOR, out->ptr, buf.ptr);

	if (!win32_find_git_in_registry(
			&buf, HKEY_LOCAL_MACHINE, REG_MSYSGIT_INSTALL, subdir) && buf.size)
		git_buf_join(out, GIT_PATH_LIST_SEPARATOR, out->ptr, buf.ptr);

	git_buf_dispose(&buf);

	return (git_buf_oom(out) ? -1 : 0);
}
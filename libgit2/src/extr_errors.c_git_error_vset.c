#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_2__ {int /*<<< orphan*/  error_buf; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int GIT_ERROR_OS ; 
 TYPE_1__* GIT_GLOBAL ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int /*<<< orphan*/  git_buf_PUTS (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_oom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_buf_vprintf (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 char* git_win32_get_error_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_error_from_buffer (int) ; 
 char* strerror (int) ; 

void git_error_vset(int error_class, const char *fmt, va_list ap)
{
#ifdef GIT_WIN32
	DWORD win32_error_code = (error_class == GIT_ERROR_OS) ? GetLastError() : 0;
#endif
	int error_code = (error_class == GIT_ERROR_OS) ? errno : 0;
	git_buf *buf = &GIT_GLOBAL->error_buf;

	git_buf_clear(buf);
	if (fmt) {
		git_buf_vprintf(buf, fmt, ap);
		if (error_class == GIT_ERROR_OS)
			git_buf_PUTS(buf, ": ");
	}

	if (error_class == GIT_ERROR_OS) {
#ifdef GIT_WIN32
		char * win32_error = git_win32_get_error_message(win32_error_code);
		if (win32_error) {
			git_buf_puts(buf, win32_error);
			git__free(win32_error);

			SetLastError(0);
		}
		else
#endif
		if (error_code)
			git_buf_puts(buf, strerror(error_code));

		if (error_code)
			errno = 0;
	}

	if (!git_buf_oom(buf))
		set_error_from_buffer(error_class);
}
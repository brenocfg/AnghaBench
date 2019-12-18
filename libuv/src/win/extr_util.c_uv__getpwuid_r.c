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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_3__ {int uid; int gid; int /*<<< orphan*/ * shell; int /*<<< orphan*/ * homedir; int /*<<< orphan*/ * username; } ;
typedef  TYPE_1__ uv_passwd_t ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetUserNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetUserProfileDirectoryW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 scalar_t__ OpenProcessToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TOKEN_READ ; 
 int /*<<< orphan*/  UNLEN ; 
 int UV_EINVAL ; 
 int UV_ENOMEM ; 
 int uv__convert_utf16_to_utf8 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uv__free (int /*<<< orphan*/ *) ; 
 int uv_translate_sys_error (int) ; 

int uv__getpwuid_r(uv_passwd_t* pwd) {
  HANDLE token;
  wchar_t username[UNLEN + 1];
  wchar_t path[MAX_PATH];
  DWORD bufsize;
  int r;

  if (pwd == NULL)
    return UV_EINVAL;

  /* Get the home directory using GetUserProfileDirectoryW() */
  if (OpenProcessToken(GetCurrentProcess(), TOKEN_READ, &token) == 0)
    return uv_translate_sys_error(GetLastError());

  bufsize = ARRAY_SIZE(path);
  if (!GetUserProfileDirectoryW(token, path, &bufsize)) {
    r = GetLastError();
    CloseHandle(token);

    /* This should not be possible */
    if (r == ERROR_INSUFFICIENT_BUFFER)
      return UV_ENOMEM;

    return uv_translate_sys_error(r);
  }

  CloseHandle(token);

  /* Get the username using GetUserNameW() */
  bufsize = ARRAY_SIZE(username);
  if (!GetUserNameW(username, &bufsize)) {
    r = GetLastError();

    /* This should not be possible */
    if (r == ERROR_INSUFFICIENT_BUFFER)
      return UV_ENOMEM;

    return uv_translate_sys_error(r);
  }

  pwd->homedir = NULL;
  r = uv__convert_utf16_to_utf8(path, -1, &pwd->homedir);

  if (r != 0)
    return r;

  pwd->username = NULL;
  r = uv__convert_utf16_to_utf8(username, -1, &pwd->username);

  if (r != 0) {
    uv__free(pwd->homedir);
    return r;
  }

  pwd->shell = NULL;
  pwd->uid = -1;
  pwd->gid = -1;

  return 0;
}
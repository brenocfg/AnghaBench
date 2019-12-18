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
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int ERROR_SUCCESS ; 
 size_t GetEnvironmentVariableW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int GetLastError () ; 
 int MAX_ENV_VAR_LENGTH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int UV_EINVAL ; 
 int UV_ENOBUFS ; 
 size_t WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int uv__convert_utf8_to_utf16 (char const*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uv__free (int /*<<< orphan*/ *) ; 
 int uv_translate_sys_error (int) ; 

int uv_os_getenv(const char* name, char* buffer, size_t* size) {
  wchar_t var[MAX_ENV_VAR_LENGTH];
  wchar_t* name_w;
  DWORD bufsize;
  size_t len;
  int r;

  if (name == NULL || buffer == NULL || size == NULL || *size == 0)
    return UV_EINVAL;

  r = uv__convert_utf8_to_utf16(name, -1, &name_w);

  if (r != 0)
    return r;

  SetLastError(ERROR_SUCCESS);
  len = GetEnvironmentVariableW(name_w, var, MAX_ENV_VAR_LENGTH);
  uv__free(name_w);
  assert(len < MAX_ENV_VAR_LENGTH); /* len does not include the null */

  if (len == 0) {
    r = GetLastError();
    if (r != ERROR_SUCCESS)
      return uv_translate_sys_error(r);
  }

  /* Check how much space we need */
  bufsize = WideCharToMultiByte(CP_UTF8, 0, var, -1, NULL, 0, NULL, NULL);

  if (bufsize == 0) {
    return uv_translate_sys_error(GetLastError());
  } else if (bufsize > *size) {
    *size = bufsize;
    return UV_ENOBUFS;
  }

  /* Convert to UTF-8 */
  bufsize = WideCharToMultiByte(CP_UTF8,
                                0,
                                var,
                                -1,
                                buffer,
                                *size,
                                NULL,
                                NULL);

  if (bufsize == 0)
    return uv_translate_sys_error(GetLastError());

  *size = bufsize - 1;
  return 0;
}
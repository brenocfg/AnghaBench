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

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int SetEnvironmentVariableW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int UV_EINVAL ; 
 int uv__convert_utf8_to_utf16 (char const*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uv__free (int /*<<< orphan*/ *) ; 
 int uv_translate_sys_error (int /*<<< orphan*/ ) ; 

int uv_os_setenv(const char* name, const char* value) {
  wchar_t* name_w;
  wchar_t* value_w;
  int r;

  if (name == NULL || value == NULL)
    return UV_EINVAL;

  r = uv__convert_utf8_to_utf16(name, -1, &name_w);

  if (r != 0)
    return r;

  r = uv__convert_utf8_to_utf16(value, -1, &value_w);

  if (r != 0) {
    uv__free(name_w);
    return r;
  }

  r = SetEnvironmentVariableW(name_w, value_w);
  uv__free(name_w);
  uv__free(value_w);

  if (r == 0)
    return uv_translate_sys_error(GetLastError());

  return 0;
}
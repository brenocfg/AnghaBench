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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  GetLastError () ; 
 int UV_EINVAL ; 
 int UV_ENOMEM ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__free (char*) ; 
 char* uv__malloc (int) ; 
 int uv_translate_sys_error (int /*<<< orphan*/ ) ; 

int uv__convert_utf16_to_utf8(const WCHAR* utf16, int utf16len, char** utf8) {
  DWORD bufsize;

  if (utf16 == NULL)
    return UV_EINVAL;

  /* Check how much space we need */
  bufsize = WideCharToMultiByte(CP_UTF8,
                                0,
                                utf16,
                                utf16len,
                                NULL,
                                0,
                                NULL,
                                NULL);

  if (bufsize == 0)
    return uv_translate_sys_error(GetLastError());

  /* Allocate the destination buffer adding an extra byte for the terminating
   * NULL. If utf16len is not -1 WideCharToMultiByte will not add it, so
   * we do it ourselves always, just in case. */
  *utf8 = uv__malloc(bufsize + 1);

  if (*utf8 == NULL)
    return UV_ENOMEM;

  /* Convert to UTF-8 */
  bufsize = WideCharToMultiByte(CP_UTF8,
                                0,
                                utf16,
                                utf16len,
                                *utf8,
                                bufsize,
                                NULL,
                                NULL);

  if (bufsize == 0) {
    uv__free(*utf8);
    *utf8 = NULL;
    return uv_translate_sys_error(GetLastError());
  }

  (*utf8)[bufsize] = '\0';
  return 0;
}
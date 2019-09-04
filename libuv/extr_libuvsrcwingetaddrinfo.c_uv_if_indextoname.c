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
typedef  int /*<<< orphan*/  NET_LUID ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CP_UTF8 ; 
 int ConvertInterfaceIndexToLuid (unsigned int,int /*<<< orphan*/ *) ; 
 int ConvertInterfaceLuidToNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  NDIS_IF_MAX_STRING_SIZE ; 
 int UV_EINVAL ; 
 int UV_ENOBUFS ; 
 size_t WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int uv_translate_sys_error (int) ; 

int uv_if_indextoname(unsigned int ifindex, char* buffer, size_t* size) {
  NET_LUID luid;
  wchar_t wname[NDIS_IF_MAX_STRING_SIZE + 1]; /* Add one for the NUL. */
  DWORD bufsize;
  int r;

  if (buffer == NULL || size == NULL || *size == 0)
    return UV_EINVAL;

  r = ConvertInterfaceIndexToLuid(ifindex, &luid);

  if (r != 0)
    return uv_translate_sys_error(r);

  r = ConvertInterfaceLuidToNameW(&luid, wname, ARRAY_SIZE(wname));

  if (r != 0)
    return uv_translate_sys_error(r);

  /* Check how much space we need */
  bufsize = WideCharToMultiByte(CP_UTF8, 0, wname, -1, NULL, 0, NULL, NULL);

  if (bufsize == 0) {
    return uv_translate_sys_error(GetLastError());
  } else if (bufsize > *size) {
    *size = bufsize;
    return UV_ENOBUFS;
  }

  /* Convert to UTF-8 */
  bufsize = WideCharToMultiByte(CP_UTF8,
                                0,
                                wname,
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
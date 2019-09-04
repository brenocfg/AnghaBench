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
typedef  int ssize_t ;
typedef  int WCHAR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 scalar_t__ GetFinalPathNameByHandleW (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LONG_PATH_PREFIX ; 
 int /*<<< orphan*/  LONG_PATH_PREFIX_LEN ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNC_PATH_PREFIX ; 
 int /*<<< orphan*/  UNC_PATH_PREFIX_LEN ; 
 int /*<<< orphan*/  VOLUME_NAME_DOS ; 
 int fs__wide_to_utf8 (int*,int,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__free (int*) ; 
 int* uv__malloc (int) ; 
 scalar_t__ wcsncmp (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t fs__realpath_handle(HANDLE handle, char** realpath_ptr) {
  int r;
  DWORD w_realpath_len;
  WCHAR* w_realpath_ptr = NULL;
  WCHAR* w_realpath_buf;

  w_realpath_len = GetFinalPathNameByHandleW(handle, NULL, 0, VOLUME_NAME_DOS);
  if (w_realpath_len == 0) {
    return -1;
  }

  w_realpath_buf = uv__malloc((w_realpath_len + 1) * sizeof(WCHAR));
  if (w_realpath_buf == NULL) {
    SetLastError(ERROR_OUTOFMEMORY);
    return -1;
  }
  w_realpath_ptr = w_realpath_buf;

  if (GetFinalPathNameByHandleW(
          handle, w_realpath_ptr, w_realpath_len, VOLUME_NAME_DOS) == 0) {
    uv__free(w_realpath_buf);
    SetLastError(ERROR_INVALID_HANDLE);
    return -1;
  }

  /* convert UNC path to long path */
  if (wcsncmp(w_realpath_ptr,
              UNC_PATH_PREFIX,
              UNC_PATH_PREFIX_LEN) == 0) {
    w_realpath_ptr += 6;
    *w_realpath_ptr = L'\\';
    w_realpath_len -= 6;
  } else if (wcsncmp(w_realpath_ptr,
                      LONG_PATH_PREFIX,
                      LONG_PATH_PREFIX_LEN) == 0) {
    w_realpath_ptr += 4;
    w_realpath_len -= 4;
  } else {
    uv__free(w_realpath_buf);
    SetLastError(ERROR_INVALID_HANDLE);
    return -1;
  }

  r = fs__wide_to_utf8(w_realpath_ptr, w_realpath_len, realpath_ptr, NULL);
  uv__free(w_realpath_buf);
  return r;
}
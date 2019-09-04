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
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetCurrentDirectoryW (int,char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  uv__free (char*) ; 
 scalar_t__ uv__malloc (size_t) ; 
 int /*<<< orphan*/  uv_fatal_error (int /*<<< orphan*/ ,char*) ; 
 char* wcsdup (char const*) ; 
 size_t wcslen (char const*) ; 
 int /*<<< orphan*/  wcsncpy (char*,char const*,size_t) ; 

__attribute__((used)) static int uv_split_path(const WCHAR* filename, WCHAR** dir,
    WCHAR** file) {
  size_t len, i;

  if (filename == NULL) {
    if (dir != NULL)
      *dir = NULL;
    *file = NULL;
    return 0;
  }

  len = wcslen(filename);
  i = len;
  while (i > 0 && filename[--i] != '\\' && filename[i] != '/');

  if (i == 0) {
    if (dir) {
      *dir = (WCHAR*)uv__malloc((MAX_PATH + 1) * sizeof(WCHAR));
      if (!*dir) {
        uv_fatal_error(ERROR_OUTOFMEMORY, "uv__malloc");
      }

      if (!GetCurrentDirectoryW(MAX_PATH, *dir)) {
        uv__free(*dir);
        *dir = NULL;
        return -1;
      }
    }

    *file = wcsdup(filename);
  } else {
    if (dir) {
      *dir = (WCHAR*)uv__malloc((i + 2) * sizeof(WCHAR));
      if (!*dir) {
        uv_fatal_error(ERROR_OUTOFMEMORY, "uv__malloc");
      }
      wcsncpy(*dir, filename, i + 1);
      (*dir)[i + 1] = L'\0';
    }

    *file = (WCHAR*)uv__malloc((len - i) * sizeof(WCHAR));
    if (!*file) {
      uv_fatal_error(ERROR_OUTOFMEMORY, "uv__malloc");
    }
    wcsncpy(*file, filename + i + 1, len - i - 1);
    (*file)[len - i - 1] = L'\0';
  }

  return 0;
}
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
 int /*<<< orphan*/  _wcsnicmp (char const*,char const*,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 char* uv__malloc (size_t) ; 
 int /*<<< orphan*/  uv_fatal_error (int /*<<< orphan*/ ,char*) ; 
 size_t wcslen (char const*) ; 
 int /*<<< orphan*/  wcsncpy (char*,char const*,size_t) ; 

__attribute__((used)) static void uv_relative_path(const WCHAR* filename,
                             const WCHAR* dir,
                             WCHAR** relpath) {
  size_t relpathlen;
  size_t filenamelen = wcslen(filename);
  size_t dirlen = wcslen(dir);
  assert(!_wcsnicmp(filename, dir, dirlen));
  if (dirlen > 0 && dir[dirlen - 1] == '\\')
    dirlen--;
  relpathlen = filenamelen - dirlen - 1;
  *relpath = uv__malloc((relpathlen + 1) * sizeof(WCHAR));
  if (!*relpath)
    uv_fatal_error(ERROR_OUTOFMEMORY, "uv__malloc");
  wcsncpy(*relpath, filename + dirlen + 1, relpathlen);
  (*relpath)[relpathlen] = L'\0';
}
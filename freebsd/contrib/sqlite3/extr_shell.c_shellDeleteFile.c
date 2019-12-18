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
 int _wunlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3_win32_utf8_to_unicode (char const*) ; 
 int unlink (char const*) ; 

int shellDeleteFile(const char *zFilename){
  int rc;
#ifdef _WIN32
  wchar_t *z = sqlite3_win32_utf8_to_unicode(zFilename);
  rc = _wunlink(z);
  sqlite3_free(z);
#else
  rc = unlink(zFilename);
#endif
  return rc;
}
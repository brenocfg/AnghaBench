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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  GET_REAL (int /*<<< orphan*/ * (*) (char const*,char const*)) ; 
 int /*<<< orphan*/  error ; 
 int /*<<< orphan*/ * fail ; 
 void* fail_close ; 
 int /*<<< orphan*/ * fail_read ; 
 void* fail_write ; 
 int /*<<< orphan*/ * real_fopen (char const*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

FILE *fopen(const char *path, const char *mode) {
  GET_REAL(fopen);
  fail = fail_read = fail_write = fail_close = 0;
  FILE *f = real_fopen(path, mode);
  error = EIO;
  if (strcmp(path, "fail_read") == 0) {
    fail = fail_read = f;
  } else if (strncmp(path, "fail_write", sizeof("fail_write") - 1) == 0) {
    // Not that jq opens files for write anyways...
    fail = fail_write = f;
    if (strcmp(path, "fail_write_enospc") == 0)
      error = ENOSPC;
  } else if (strncmp(path, "fail_close", sizeof("fail_close") - 1) == 0) {
    fail = fail_close = f;
    if (strcmp(path, "fail_close_enospc") == 0)
      error = ENOSPC;
  }
  return f;
}
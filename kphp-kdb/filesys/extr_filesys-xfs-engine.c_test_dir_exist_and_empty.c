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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  file_t ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free_filelist (int /*<<< orphan*/ *) ; 
 int getdir (char const* const,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kprintf (char*,char const* const,...) ; 
 scalar_t__ stat (char const* const,struct stat*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,char const* const) ; 

__attribute__((used)) static int test_dir_exist_and_empty (const char *const path, struct stat *b) {
  if (stat (path, b) || !S_ISDIR (b->st_mode)) {
    kprintf ("Directory %s doesn't exist\n", path);
    exit (1);
  }

  file_t *px;
  int n = getdir (path, &px, 0, 1);
  free_filelist (px);
  if (n < 0) {
    kprintf ("getdir (%s) returns error code %d.\n", path, n);
    exit (1);
  }
  if (n > 0) {
    vkprintf (1, "%s isn't empty directory!\n", path);
    return 0;
  }
  return 1;
}
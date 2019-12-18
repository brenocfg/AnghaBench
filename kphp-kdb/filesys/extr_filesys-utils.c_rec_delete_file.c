#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_4__ {char const* filename; struct stat st; struct TYPE_4__* next; } ;
typedef  TYPE_1__ file_t ;

/* Variables and functions */
 int PATH_MAX ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_filelist (TYPE_1__*) ; 
 int getdir (char const*,TYPE_1__**,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rmdir (char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ unlink (char const*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,char const*) ; 

__attribute__((used)) static int rec_delete_file (const char *path, struct stat *S) {
  char a[PATH_MAX];
  if (S_ISLNK (S->st_mode)) {
    if (unlink (path)) {
      vkprintf (1, "unlink (%s) failed. %m\n", path);
      return -5;
    }
  } else if (S_ISDIR (S->st_mode)) {
    int l = strlen (path);
    file_t *px, *p;
    int n = getdir (path, &px, 0, 1);
    if (n < 0) {
      return -2;
    }
    for (p = px; p != NULL; p = p->next) {
      int m = l + 2 + strlen (p->filename);
      if (PATH_MAX < m) {
        return -6;
      }
      sprintf (a, "%s/%s", path, p->filename);
      if (rec_delete_file (a, &p->st) < 0) {
        return -3;
      }
    }
    free_filelist (px);
    if (rmdir (path)) {
      vkprintf (1, "rmdir (%s) failed. %m\n", path);
      return -7;
    }
  } else {
    if (unlink (path)) {
      return -4;
    }
  }
  return 0;
}
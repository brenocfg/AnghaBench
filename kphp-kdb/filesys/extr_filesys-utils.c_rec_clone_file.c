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
struct stat {char* st_mode; } ;
struct TYPE_4__ {char* filename; struct stat st; struct TYPE_4__* next; } ;
typedef  TYPE_1__ file_t ;

/* Variables and functions */
 int PATH_MAX ; 
 scalar_t__ S_ISDIR (char*) ; 
 scalar_t__ S_ISLNK (char*) ; 
 int /*<<< orphan*/  free_filelist (TYPE_1__*) ; 
 int getdir (char*,TYPE_1__**,int /*<<< orphan*/ ,int) ; 
 scalar_t__ lcopy_attrs (char*,struct stat*) ; 
 scalar_t__ link (char*,char*) ; 
 scalar_t__ mkdir (char*,char*) ; 
 int readlink (char*,char*,int) ; 
 int snprintf (char*,int,char*,char const* const,char*) ; 
 scalar_t__ symlink (char*,char*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,char*,char*) ; 

__attribute__((used)) static int rec_clone_file (const char *const src_path, const char *const dst_path, char *path, struct stat *S) {
  char a[PATH_MAX], b[PATH_MAX];
  if (S_ISLNK (S->st_mode)) {
    if (snprintf (a, PATH_MAX, "%s/%s", src_path, path) >= PATH_MAX) {
      return -1;
    }
    int r = readlink (a, b, PATH_MAX);
    if (r < 0 || r >= PATH_MAX) {
      return -4;
    }
    b[r] = 0;
    if (snprintf (a, PATH_MAX, "%s/%s", dst_path, path) >= PATH_MAX) {
      return -1;
    }
    if (symlink (b, a) < 0) {
      vkprintf (1, "symlink (%s, %s) failed. %m\n", b, a);
      return -5;
    }
    if (lcopy_attrs (a, S) < 0) {
      return -6;
    }
  } else if (S_ISDIR (S->st_mode)) {
    if (snprintf (a, PATH_MAX, "%s/%s", dst_path, path) >= PATH_MAX) {
      return -1;
    }
    if (mkdir (a, S->st_mode)) {
      vkprintf (1, "mkdir (%s, %d) fail. %m\n", a, S->st_mode);
      return -2;
    }
    if (snprintf (a, PATH_MAX, "%s/%s", src_path, path) >= PATH_MAX) {
      return -1;
    }
    file_t *px, *p;
    int n = getdir (a, &px, 0, 1);
    if (n < 0) {
      return -2;
    }
    for (p = px; p != NULL; p = p->next) {
      if (snprintf (a, PATH_MAX, "%s/%s", path, p->filename) >= PATH_MAX) {
        return -1;
      }
      if (rec_clone_file (src_path, dst_path, a, &p->st) < 0) {
        return -3;
      }
    }
    free_filelist (px);
    if (snprintf (a, PATH_MAX, "%s/%s", dst_path, path) >= PATH_MAX) {
      return -1;
    }
    if (lcopy_attrs (a, S) < 0) {
      return -7;
    }
  } else {
    if (snprintf (a, PATH_MAX, "%s/%s", src_path, path) >= PATH_MAX || snprintf (b, PATH_MAX, "%s/%s", dst_path, path) >= PATH_MAX) {
      return -1;
    }
    if (link (a, b) < 0) {
      vkprintf (1, "link (%s, %s) fail. %m\n", a, b);
      return -1;
    }
  }
  return 0;
}
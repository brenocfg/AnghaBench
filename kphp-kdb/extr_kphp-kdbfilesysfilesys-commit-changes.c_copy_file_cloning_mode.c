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

/* Variables and functions */
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int PATH_MAX ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ close (int) ; 
 int lcopy_attrs (char*,struct stat*) ; 
 scalar_t__ mkdir (char*,int /*<<< orphan*/ ) ; 
 int open (char*,int const,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ symlink (char*,char*) ; 
 char* tmp_dir ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 
 int write (int,unsigned char*,int) ; 

__attribute__((used)) static int copy_file_cloning_mode (struct stat *S, char *name, unsigned char *buf, int l, int same) {
  char a[PATH_MAX];
  if (snprintf (a, PATH_MAX, "%s/%s", tmp_dir, name) >= PATH_MAX) {
    return -1;
  }
  if (!same) {
    if (S_ISLNK (S->st_mode)) {
      unlink (a);
      if (symlink ((char *) buf, a) < 0) {
        vkprintf (1, "%m\n");
        return -7;
      }
    } else if (S_ISDIR (S->st_mode)) {
      if (mkdir (a, S->st_mode) < 0) {
        vkprintf (1, "mkdir (%s, %d) failed. %m\n", a, S->st_mode);
        return -6;
      }
    } else {
      const int flags = O_CREAT | O_TRUNC | O_WRONLY;
      int fd = open (a, flags, S->st_mode);
      if (fd < 0) {
        vkprintf (1, "open (%s, %d, %d) fail. %m\n", a, flags, S->st_mode);
        return -2;
      }
      int sz = write (fd, buf, l);
      if (sz != l) {
        vkprintf (1, "%d bytes of %d was written to %s. %m\n", sz, l, a);
        return -3;
      }
      if (close (fd)) {
        vkprintf (1, "closing %s failed. %m\n", a);
        return -4;
      }
    }
  }
  int r = lcopy_attrs (a, S);
  if (r < 0) {
    vkprintf (1, "lcopy_attrs returns error code %d.\n", r);
    return -5;
  }

  return 0;
}
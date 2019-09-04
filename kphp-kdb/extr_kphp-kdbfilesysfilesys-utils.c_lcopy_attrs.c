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
typedef  int /*<<< orphan*/  times ;
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct stat {int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ chmod (char*,int /*<<< orphan*/ ) ; 
 int errno ; 
 scalar_t__ lchown (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lutimes (char*,struct timeval*) ; 
 int /*<<< orphan*/  memset (struct timeval*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ utimes (char*,struct timeval*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,char*) ; 

int lcopy_attrs (char *filename, struct stat *S)  {
  if (!S_ISLNK (S->st_mode)) {
    if (chmod (filename, S->st_mode) < 0) {
      vkprintf (1, "chmod for %s failed. %m\n", filename);
      return -1;
    }
  }
  if (lchown (filename, S->st_uid, S->st_gid) < 0) {
    vkprintf (1, "lchown for %s failed. %m\n", filename);
    return -1;
  }
  struct timeval times[2];
  memset (times, 0, sizeof (times));
  times[0].tv_sec = S->st_atime;
  times[1].tv_sec = S->st_mtime;
  errno = 0;
  if (lutimes (filename, times) < 0) {
    int err = errno;
    vkprintf (1, "lutimes for %s failed. %m\n", filename);
    if (err == ENOSYS && !S_ISLNK (S->st_mode)) {
      if (utimes (filename, times) < 0) {
        vkprintf (1, "utimes for %s failed. %m\n", filename);
        return -3;
      }
      errno = 0;
      return 0;
    }
    return -2;
  }
  return 0;
}
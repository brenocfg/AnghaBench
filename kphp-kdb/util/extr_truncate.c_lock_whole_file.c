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
struct flock {int l_type; scalar_t__ l_len; scalar_t__ l_start; int /*<<< orphan*/  l_whence; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETLK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,struct flock*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

int lock_whole_file (int fd, int mode) {
  static struct flock L;
  L.l_type = mode;
  L.l_whence = SEEK_SET;
  L.l_start = 0;
  L.l_len = 0;
  if (fcntl (fd, F_SETLK, &L) < 0) {
    fprintf (stderr, "cannot lock file %d: %m\n", fd);
    return -1;
  }
  return 1;
}
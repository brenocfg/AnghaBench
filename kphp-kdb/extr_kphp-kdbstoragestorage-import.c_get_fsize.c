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
typedef  int /*<<< orphan*/  time_t ;
struct stat {int st_size; int /*<<< orphan*/  st_mtime; } ;

/* Variables and functions */
 scalar_t__ fstat (int,struct stat*) ; 

__attribute__((used)) static int get_fsize (int fd, time_t *mtime) {
  struct stat buf;
  if (fstat (fd, &buf)) {
    return -1;
  }
  if (mtime) {
    *mtime = buf.st_mtime;
  }
  return buf.st_size;
}
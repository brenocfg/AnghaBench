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

/* Variables and functions */
 scalar_t__ BUFFSIZE ; 
 scalar_t__ Buff ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  assert (int) ; 
 int buffered_write ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  kprintf (char*,char*) ; 
 scalar_t__ lock_whole_file (int,int /*<<< orphan*/ ) ; 
 int open (char*,int,int) ; 
 scalar_t__ rptr ; 
 scalar_t__ wptr ; 
 int write_fd ; 
 char* write_filename ; 
 scalar_t__ write_off ; 

__attribute__((used)) static int open_write_fd (char *filename, int bwrite, int ofd) {
  buffered_write = bwrite;
  write_filename = filename;
  rptr = wptr = Buff + BUFFSIZE;
  write_off = 0;
  if (ofd < 0) {
    ofd = open (filename, O_CREAT | O_WRONLY | O_EXCL, 0640);
    if (ofd < 0) {
      kprintf ("open (%s, O_CREAT | O_WRONLY | O_EXCL, 0640) failed. %m\n", filename);
      return -1;
    }
    assert (ofd > 1);
    if (lock_whole_file (ofd, F_WRLCK) <= 0) {
      kprintf ("cannot lock file '%s' for writing\n", filename);
      assert (!close (ofd));
      return -1;
    }
  } else {
    assert (ofd == 1);
  }
  return write_fd = ofd;
}
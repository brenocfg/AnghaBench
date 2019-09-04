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
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ verbosity ; 
 scalar_t__* wptr ; 
 int write (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__* write_buff ; 
 int /*<<< orphan*/ * write_fd ; 

void flush_write (int x) {
  //fprintf (stderr, "%d - %d\n", x, write_fd[x]);
  if (verbosity) {
    fprintf (stderr, "writing %ld bytes to file %d\n", (long)(wptr[x] - write_buff[x]), x);
  }
  if (wptr[x] != write_buff[x]) {
    int r = write (write_fd[x], write_buff[x], wptr[x] - write_buff[x]);
    if (r <= 0) {
      fprintf (stderr, "error_code %d (%s)\n", r, strerror (errno));
      exit (2);
    }
    if (r != wptr[x] - write_buff[x]) {
      fprintf (stderr, "written only part...\n");
      exit (2);
    }
  }
  wptr[x] = write_buff[x];
}
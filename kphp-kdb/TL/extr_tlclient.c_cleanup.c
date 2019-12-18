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
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  epoll_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__* history_filename ; 
 int /*<<< orphan*/ * log_file ; 
 int /*<<< orphan*/  sfd ; 
 int /*<<< orphan*/  write_history (scalar_t__*) ; 

void cleanup (void) {
  if (history_filename[0]) {
    write_history (history_filename);
  }
  epoll_close (sfd);
  close (sfd);

  if (log_file) {
    fclose (log_file);
    log_file = NULL;
  }
}
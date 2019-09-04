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
 scalar_t__ SIGTERM_WAIT_TIMEOUT ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  epoll_close (int) ; 
 int hts_stopped ; 
 int http_sfd ; 
 scalar_t__ precise_now ; 
 scalar_t__ sigterm_time ; 

void hts_stop() {
  if (hts_stopped) {
    return;
  }
  if (http_sfd != -1) {
    epoll_close (http_sfd);
    close (http_sfd);
    http_sfd = -1;
  }
  sigterm_time = precise_now + SIGTERM_WAIT_TIMEOUT;
  hts_stopped = 1;
}
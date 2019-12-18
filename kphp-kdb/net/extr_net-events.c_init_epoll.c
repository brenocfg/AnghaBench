#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int fd; } ;

/* Variables and functions */
 TYPE_1__* Events ; 
 int /*<<< orphan*/  MAX_EVENTS ; 
 int epoll_create (int /*<<< orphan*/ ) ; 
 int epoll_fd ; 
 int /*<<< orphan*/  perror (char*) ; 

int init_epoll (void) {
  int fd;
  if (epoll_fd) return 0;
  Events[0].fd = -1;
  fd = epoll_create (MAX_EVENTS);
  if (fd < 0) {
    perror ("epoll_create()");
    return -1;
  }
  epoll_fd = fd;
  return fd;
}
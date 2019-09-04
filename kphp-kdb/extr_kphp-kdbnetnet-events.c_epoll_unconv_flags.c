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
 int EPOLLERR ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLPRI ; 
 int EPOLLRDHUP ; 
 int EVT_FROM_EPOLL ; 
 int EVT_READ ; 
 int EVT_SPEC ; 
 int EVT_WRITE ; 

int epoll_unconv_flags (int f) {
  int r = EVT_FROM_EPOLL;
  if (f & (EPOLLIN | EPOLLERR)) {
    r |= EVT_READ;
  }
  if (f & EPOLLOUT) {
    r |= EVT_WRITE;
  }
  if (f & (EPOLLRDHUP | EPOLLPRI)) {
    r |= EVT_SPEC;
  }
  return r;
}
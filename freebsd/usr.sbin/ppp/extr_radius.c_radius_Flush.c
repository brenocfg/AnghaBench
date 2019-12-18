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
struct timeval {int /*<<< orphan*/  tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_2__ {int fd; } ;
struct radius {TYPE_1__ cx; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TICKUNIT ; 
 int /*<<< orphan*/  radius_Continue (struct radius*,int) ; 
 int /*<<< orphan*/  select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

void
radius_Flush(struct radius *r)
{
  struct timeval tv;
  fd_set s;

  while (r->cx.fd != -1) {
    FD_ZERO(&s);
    FD_SET(r->cx.fd, &s);
    tv.tv_sec = 0;
    tv.tv_usec = TICKUNIT;
    select(r->cx.fd + 1, &s, NULL, NULL, &tv);
    radius_Continue(r, 1);
  }
}
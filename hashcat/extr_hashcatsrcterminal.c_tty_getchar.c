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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int getchar () ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  stdin ; 

int tty_getchar()
{
  fd_set rfds;

  FD_ZERO (&rfds);

  FD_SET (fileno (stdin), &rfds);

  struct timeval tv;

  tv.tv_sec  = 1;
  tv.tv_usec = 0;

  int retval = select (1, &rfds, NULL, NULL, &tv);

  if (retval ==  0) return  0;
  if (retval == -1) return -1;

  return getchar();
}
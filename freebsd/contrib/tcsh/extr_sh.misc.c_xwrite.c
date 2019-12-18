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
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 scalar_t__ handle_pending_signals () ; 
 int write (int,void const*,size_t) ; 

ssize_t
xwrite(int fildes, const void *buf, size_t nbyte)
{
    ssize_t res = -1;

    /* This is where we will be blocked most of the time, so handle signals
       that didn't interrupt any system call. */
    do
      if (handle_pending_signals())
	  break;
    while ((res = write(fildes, buf, nbyte)) == -1 && errno == EINTR);
    return res;
}
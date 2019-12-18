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
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct serial {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCSBRK ; 
 int /*<<< orphan*/  TIOCCBRK ; 
 int /*<<< orphan*/  TIOCSBRK ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  select (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*) ; 
 int tcsendbreak (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hardwire_send_break (struct serial *scb)
{
#ifdef HAVE_TERMIOS
  return tcsendbreak (scb->fd, 0);
#endif

#ifdef HAVE_TERMIO
  return ioctl (scb->fd, TCSBRK, 0);
#endif

#ifdef HAVE_SGTTY
  {
    int status;
    struct timeval timeout;

    status = ioctl (scb->fd, TIOCSBRK, 0);

    /* Can't use usleep; it doesn't exist in BSD 4.2.  */
    /* Note that if this select() is interrupted by a signal it will not wait
       the full length of time.  I think that is OK.  */
    timeout.tv_sec = 0;
    timeout.tv_usec = 250000;
    select (0, 0, 0, 0, &timeout);
    status = ioctl (scb->fd, TIOCCBRK, 0);
    return status;
  }
#endif
}
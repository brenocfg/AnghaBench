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
struct serial {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCFLSH ; 
 int /*<<< orphan*/  TCIFLUSH ; 
 int /*<<< orphan*/  TIOCFLUSH ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ser_unix_flush_input (struct serial*) ; 
 int tcflush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hardwire_flush_input (struct serial *scb)
{
  ser_unix_flush_input (scb);

#ifdef HAVE_TERMIOS
  return tcflush (scb->fd, TCIFLUSH);
#endif

#ifdef HAVE_TERMIO
  return ioctl (scb->fd, TCFLSH, 0);
#endif

#ifdef HAVE_SGTTY
  /* This flushes both input and output, but we can't do better.  */
  return ioctl (scb->fd, TIOCFLUSH, 0);
#endif
}
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
struct serial {scalar_t__ fd; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int SERIAL_ERROR ; 
 int SERIAL_TIMEOUT ; 
 scalar_t__ errno ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct timeval*) ; 

int
ser_unix_wait_for (struct serial *scb, int timeout)
{
  while (1)
    {
      int numfds;
      struct timeval tv;
      fd_set readfds, exceptfds;

      /* NOTE: Some OS's can scramble the READFDS when the select()
         call fails (ex the kernel with Red Hat 5.2).  Initialize all
         arguments before each call. */

      tv.tv_sec = timeout;
      tv.tv_usec = 0;

      FD_ZERO (&readfds);
      FD_ZERO (&exceptfds);
      FD_SET (scb->fd, &readfds);
      FD_SET (scb->fd, &exceptfds);

      if (timeout >= 0)
	numfds = select (scb->fd + 1, &readfds, 0, &exceptfds, &tv);
      else
	numfds = select (scb->fd + 1, &readfds, 0, &exceptfds, 0);

      if (numfds <= 0)
	{
	  if (numfds == 0)
	    return SERIAL_TIMEOUT;
	  else if (errno == EINTR)
	    continue;
	  else
	    return SERIAL_ERROR;	/* Got an error from select or poll */
	}

      return 0;
    }
}
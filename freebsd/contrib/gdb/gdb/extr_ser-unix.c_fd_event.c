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
struct serial {scalar_t__ bufcnt; int /*<<< orphan*/  async_context; int /*<<< orphan*/  (* async_handler ) (struct serial*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  buf; int /*<<< orphan*/  bufp; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSIZ ; 
 scalar_t__ EINTR ; 
 scalar_t__ SERIAL_EOF ; 
 void* SERIAL_ERROR ; 
 scalar_t__ errno ; 
 int read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reschedule (struct serial*) ; 
 int /*<<< orphan*/  stub1 (struct serial*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fd_event (int error, void *context)
{
  struct serial *scb = context;
  if (error != 0)
    {
      scb->bufcnt = SERIAL_ERROR;
    }
  else if (scb->bufcnt == 0)
    {
      /* Prime the input FIFO.  The readchar() function is used to
         pull characters out of the buffer.  See also
         generic_readchar(). */
      int nr;
      do
	{
	  nr = read (scb->fd, scb->buf, BUFSIZ);
	}
      while (nr == -1 && errno == EINTR);
      if (nr == 0)
	{
	  scb->bufcnt = SERIAL_EOF;
	}
      else if (nr > 0)
	{
	  scb->bufcnt = nr;
	  scb->bufp = scb->buf;
	}
      else
	{
	  scb->bufcnt = SERIAL_ERROR;
	}
    }
  scb->async_handler (scb, scb->async_context);
  reschedule (scb);
}
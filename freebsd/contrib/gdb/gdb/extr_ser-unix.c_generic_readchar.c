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
struct serial {int bufcnt; int* bufp; } ;
typedef  enum serial_rc { ____Placeholder_serial_rc } serial_rc ;

/* Variables and functions */
#define  SERIAL_EOF 130 
#define  SERIAL_ERROR 129 
#define  SERIAL_TIMEOUT 128 
 int /*<<< orphan*/  reschedule (struct serial*) ; 

__attribute__((used)) static int
generic_readchar (struct serial *scb, int timeout,
		  int (do_readchar) (struct serial *scb, int timeout))
{
  int ch;
  if (scb->bufcnt > 0)
    {
      ch = *scb->bufp;
      scb->bufcnt--;
      scb->bufp++;
    }
  else if (scb->bufcnt < 0)
    {
      /* Some errors/eof are are sticky. */
      ch = scb->bufcnt;
    }
  else
    {
      ch = do_readchar (scb, timeout);
      if (ch < 0)
	{
	  switch ((enum serial_rc) ch)
	    {
	    case SERIAL_EOF:
	    case SERIAL_ERROR:
	      /* Make the error/eof stick. */
	      scb->bufcnt = ch;
	      break;
	    case SERIAL_TIMEOUT:
	      scb->bufcnt = 0;
	      break;
	    }
	}
    }
  reschedule (scb);
  return ch;
}
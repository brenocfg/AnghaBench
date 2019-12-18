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
struct serial {size_t fd; } ;
struct dos_ttystate {int txbusy; scalar_t__ base; scalar_t__ fifo; } ;

/* Variables and functions */
 size_t CNT_TX ; 
 int /*<<< orphan*/  EIO ; 
 long RAWHZ ; 
 int SERIAL_ERROR ; 
 int* cnts ; 
 scalar_t__ com_data ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  outportb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outportsb (scalar_t__,char const*,int) ; 
 struct dos_ttystate* ports ; 
 long rawclock () ; 

__attribute__((used)) static int
dos_write (struct serial *scb, const char *str, int len)
{
  volatile struct dos_ttystate *port = &ports[scb->fd];
  int fifosize = port->fifo ? 16 : 1;
  long then;
  int cnt;

  while (len > 0)
    {
      /* send the data, fifosize bytes at a time */
      cnt = fifosize > len ? len : fifosize;
      port->txbusy = 1;
      /* Francisco Pastor <fpastor.etra-id@etra.es> says OUTSB messes
	 up the communications with UARTs with FIFOs.  */
#ifdef UART_FIFO_WORKS
      outportsb (port->base + com_data, str, cnt);
      str += cnt;
      len -= cnt;
#else
      for ( ; cnt > 0; cnt--, len--)
	outportb (port->base + com_data, *str++);
#endif
#ifdef DOS_STATS
      cnts[CNT_TX] += cnt;
#endif
      /* wait for transmission to complete (max 1 sec) */
      then = rawclock () + RAWHZ;
      while (port->txbusy)
	{
	  if ((rawclock () - then) >= 0)
	    {
	      errno = EIO;
	      return SERIAL_ERROR;
	    }
	}
    }
  return 0;
}
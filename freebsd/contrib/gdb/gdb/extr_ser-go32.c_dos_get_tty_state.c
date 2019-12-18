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
struct dos_ttystate {scalar_t__ refcnt; } ;
typedef  int /*<<< orphan*/ * serial_ttystate ;

/* Variables and functions */
 int /*<<< orphan*/  isatty (int) ; 
 struct dos_ttystate* ports ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static serial_ttystate
dos_get_tty_state (struct serial *scb)
{
  struct dos_ttystate *port = &ports[scb->fd];
  struct dos_ttystate *state;

  /* Are they asking about a port we opened?  */
  if (port->refcnt <= 0)
    {
      /* We've never heard about this port.  We should fail this call,
	 unless they are asking about one of the 3 standard handles,
	 in which case we pretend the handle was open by us if it is
	 connected to a terminal device.  This is beacuse Unix
	 terminals use the serial interface, so GDB expects the
	 standard handles to go through here.  */
      if (scb->fd >= 3 || !isatty (scb->fd))
	return NULL;
    }

  state = (struct dos_ttystate *) xmalloc (sizeof *state);
  *state = *port;
  return (serial_ttystate) state;
}
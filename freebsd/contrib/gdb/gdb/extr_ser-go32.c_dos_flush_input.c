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
struct dos_ttystate {scalar_t__ fifo; scalar_t__ count; scalar_t__ first; } ;

/* Variables and functions */
 int FIFO_ENABLE ; 
 int FIFO_RCV_RST ; 
 int FIFO_TRIGGER ; 
 int /*<<< orphan*/  com_fifo ; 
 int /*<<< orphan*/  disable () ; 
 int /*<<< orphan*/  enable () ; 
 int /*<<< orphan*/  outb (struct dos_ttystate*,int /*<<< orphan*/ ,int) ; 
 struct dos_ttystate* ports ; 

__attribute__((used)) static int
dos_flush_input (struct serial *scb)
{
  struct dos_ttystate *port = &ports[scb->fd];
  disable ();
  port->first = port->count = 0;
  if (port->fifo)
    outb (port, com_fifo, FIFO_ENABLE | FIFO_RCV_RST | FIFO_TRIGGER);
  enable ();
  return 0;
}
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
struct dos_ttystate {int dummy; } ;

/* Variables and functions */
 int RAWHZ ; 
 int SERIAL_TIMEOUT ; 
 int dos_getc (struct dos_ttystate*) ; 
 struct dos_ttystate* ports ; 
 long rawclock () ; 

__attribute__((used)) static int
dos_readchar (struct serial *scb, int timeout)
{
  struct dos_ttystate *port = &ports[scb->fd];
  long then;
  int c;

  then = rawclock () + (timeout * RAWHZ);
  while ((c = dos_getc (port)) < 0)
    {
      if (timeout >= 0 && (rawclock () - then) >= 0)
	return SERIAL_TIMEOUT;
    }

  return c;
}
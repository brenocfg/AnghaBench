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
struct serial {int dummy; } ;

/* Variables and functions */
 struct serial* serial_open (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static struct serial *
remote_serial_open (char *name)
{
  static int udp_warning = 0;

  /* FIXME: Parsing NAME here is a hack.  But we want to warn here instead
     of in ser-tcp.c, because it is the remote protocol assuming that the
     serial connection is reliable and not the serial connection promising
     to be.  */
  if (!udp_warning && strncmp (name, "udp:", 4) == 0)
    {
      warning ("The remote protocol may be unreliable over UDP.");
      warning ("Some events may be lost, rendering further debugging "
	       "impossible.");
      udp_warning = 1;
    }

  return serial_open (name);
}
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
 int SERIAL_TIMEOUT ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fputc_unfiltered (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 scalar_t__ remote_debug ; 
 int serial_readchar (struct serial*,int) ; 

__attribute__((used)) static int
readchar (struct serial *desc, int timeout)
{
  int c;

  c = serial_readchar (desc, timeout);

  if (remote_debug > 0)
    fputc_unfiltered (c, gdb_stdlog);

  if (c >= 0)
    return c;

  if (c == SERIAL_TIMEOUT)
    error ("Timeout reading from remote system.");

  perror_with_name ("xmodem.c:readchar()");
}
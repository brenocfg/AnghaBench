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

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 scalar_t__ remote_break ; 
 scalar_t__ remote_debug ; 
 int /*<<< orphan*/  remote_desc ; 
 int /*<<< orphan*/  serial_send_break (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
remote_stop (void)
{
  /* Send a break or a ^C, depending on user preference.  */
  if (remote_debug)
    fprintf_unfiltered (gdb_stdlog, "remote_stop called\n");

  if (remote_break)
    serial_send_break (remote_desc);
  else
    serial_write (remote_desc, "\003", 1);
}
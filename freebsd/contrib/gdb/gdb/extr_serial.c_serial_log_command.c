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
 int /*<<< orphan*/  fputs_unfiltered (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 char serial_current_type ; 
 int /*<<< orphan*/  serial_logfp ; 

void
serial_log_command (const char *cmd)
{
  if (!serial_logfp)
    return;

  serial_current_type = 'c';

  fputs_unfiltered ("\nc ", serial_logfp);
  fputs_unfiltered (cmd, serial_logfp);

  /* Make sure that the log file is as up-to-date as possible,
     in case we are getting ready to dump core or something. */
  gdb_flush (serial_logfp);
}
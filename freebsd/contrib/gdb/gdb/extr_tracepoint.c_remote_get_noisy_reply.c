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
 int /*<<< orphan*/  QUIT ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  getpkt (char*,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote_console_output (char*) ; 
 int /*<<< orphan*/  trace_error (char*) ; 

__attribute__((used)) static char *
remote_get_noisy_reply (char *buf,
			long sizeof_buf)
{
  do				/* loop on reply from remote stub */
    {
      QUIT;			/* allow user to bail out with ^C */
      getpkt (buf, sizeof_buf, 0);
      if (buf[0] == 0)
	error ("Target does not support this command.");
      else if (buf[0] == 'E')
	trace_error (buf);
      else if (buf[0] == 'O' &&
	       buf[1] != 'K')
	remote_console_output (buf + 1);	/* 'O' message from stub */
      else
	return buf;		/* here's the actual reply */
    }
  while (1);
}
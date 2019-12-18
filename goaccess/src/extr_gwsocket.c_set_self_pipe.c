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
 int /*<<< orphan*/  FATAL (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int pipe (int*) ; 
 int /*<<< orphan*/  set_nonblocking (int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void
set_self_pipe (int *self_pipe)
{
  /* Initialize self pipe. */
  if (pipe (self_pipe) == -1)
    FATAL ("Unable to create pipe: %s.", strerror (errno));

  /* make the read and write pipe non-blocking */
  set_nonblocking (self_pipe[0]);
  set_nonblocking (self_pipe[1]);
}
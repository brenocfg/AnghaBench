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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ myattach (int) ; 
 unsigned char mywait (char*,int /*<<< orphan*/ ) ; 
 int signal_pid ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
attach_inferior (int pid, char *statusptr, unsigned char *sigptr)
{
  /* myattach should return -1 if attaching is unsupported,
     0 if it succeeded, and call error() otherwise.  */

  if (myattach (pid) != 0)
    return -1;

  fprintf (stderr, "Attached; pid = %d\n", pid);

  /* FIXME - It may be that we should get the SIGNAL_PID from the
     attach function, so that it can be the main thread instead of
     whichever we were told to attach to.  */
  signal_pid = pid;

  *sigptr = mywait (statusptr, 0);

  return 0;
}
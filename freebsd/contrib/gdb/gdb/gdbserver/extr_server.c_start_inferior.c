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
 int /*<<< orphan*/  SIGTTIN ; 
 int /*<<< orphan*/  SIGTTOU ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int create_inferior (char*,char**) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 unsigned char mywait (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int signal_pid ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tcsetpgrp (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned char
start_inferior (char *argv[], char *statusptr)
{
  signal (SIGTTOU, SIG_DFL);
  signal (SIGTTIN, SIG_DFL);

  signal_pid = create_inferior (argv[0], argv);

  fprintf (stderr, "Process %s created; pid = %d\n", argv[0],
	   signal_pid);

  signal (SIGTTOU, SIG_IGN);
  signal (SIGTTIN, SIG_IGN);
  tcsetpgrp (fileno (stderr), signal_pid);

  /* Wait till we are at 1st instruction in program, return signal number.  */
  return mywait (statusptr, 0);
}
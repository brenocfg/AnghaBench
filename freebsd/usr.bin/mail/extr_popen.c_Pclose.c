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
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int file_pid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_file (int /*<<< orphan*/ *) ; 
 int wait_child (int) ; 

int
Pclose(FILE *ptr)
{
	int i;
	sigset_t nset, oset;

	i = file_pid(ptr);
	unregister_file(ptr);
	(void)fclose(ptr);
	(void)sigemptyset(&nset);
	(void)sigaddset(&nset, SIGINT);
	(void)sigaddset(&nset, SIGHUP);
	(void)sigprocmask(SIG_BLOCK, &nset, &oset);
	i = wait_child(i);
	(void)sigprocmask(SIG_SETMASK, &oset, NULL);
	return (i);
}
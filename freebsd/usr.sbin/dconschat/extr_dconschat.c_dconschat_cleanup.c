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
struct dcons_state {int /*<<< orphan*/  tsave; } ;

/* Variables and functions */
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  TCSADRAIN ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 struct dcons_state sc ; 
 scalar_t__ tc_set ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait (int*) ; 

__attribute__((used)) static void
dconschat_cleanup(int sig)
{
	struct dcons_state *dc;
	int status;

	dc = &sc;
	if (tc_set != 0)
		tcsetattr(STDIN_FILENO, TCSADRAIN, &dc->tsave);

	if (sig > 0)
		printf("\n[dconschat exiting with signal %d ...]\n", sig);
	else
		printf("\n[dconschat exiting...]\n");
	wait(&status);
	exit(0);
}
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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int background ; 
 int /*<<< orphan*/  daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int getpid () ; 
 int /*<<< orphan*/  pidName ; 

__attribute__((used)) static void DaemonMode(void)
{
	FILE*	pidFile;

	daemon (0, 0);
	background = 1;

	pidFile = fopen (pidName, "w");
	if (pidFile) {

		fprintf (pidFile, "%d\n", getpid ());
		fclose (pidFile);
	}
}
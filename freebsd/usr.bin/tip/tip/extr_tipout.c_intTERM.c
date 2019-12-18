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
 int /*<<< orphan*/  SCRIPT ; 
 scalar_t__ boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fscript ; 
 int /*<<< orphan*/  kill (scalar_t__,int) ; 
 scalar_t__ tipin_pid ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intTERM(int signo)
{
	if (boolean(value(SCRIPT)) && fscript != NULL)
		fclose(fscript);
	if (signo && tipin_pid)
		kill(tipin_pid, signo);
	exit(0);
}
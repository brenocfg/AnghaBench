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
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int code ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* remotecwd ; 
 int /*<<< orphan*/  ttyout ; 
 int /*<<< orphan*/  updateremotecwd () ; 

void
pwd(int argc, char *argv[])
{

	code = -1;
	if (argc != 1) {
		UPRINTF("usage: %s\n", argv[0]);
		return;
	}
	if (! remotecwd[0])
		updateremotecwd();
	if (! remotecwd[0])
		fprintf(ttyout, "Unable to determine remote directory\n");
	else {
		fprintf(ttyout, "Remote directory: %s\n", remotecwd);
		code = 0;
	}
}
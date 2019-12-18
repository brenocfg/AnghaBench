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
 char* localcwd ; 
 int /*<<< orphan*/  ttyout ; 
 int /*<<< orphan*/  updatelocalcwd () ; 

void
lpwd(int argc, char *argv[])
{

	code = -1;
	if (argc != 1) {
		UPRINTF("usage: %s\n", argv[0]);
		return;
	}
	if (! localcwd[0])
		updatelocalcwd();
	if (! localcwd[0])
		fprintf(ttyout, "Unable to determine local directory\n");
	else {
		fprintf(ttyout, "Local directory: %s\n", localcwd);
		code = 0;
	}
}
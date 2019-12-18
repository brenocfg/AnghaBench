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
 char* formname ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ttyout ; 

void
setform(int argc, char *argv[])
{

	if (argc != 2) {
		UPRINTF("usage: %s format\n", argv[0]);
		code = -1;
		return;
	}
	fprintf(ttyout, "We only support %s format, sorry.\n", formname);
	code = -1;
}
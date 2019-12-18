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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* structname ; 
 int /*<<< orphan*/  ttyout ; 

void
setstruct(int argc, char *argv[])
{

	if (argc != 2) {
		UPRINTF("usage: %s struct-mode\n", argv[0]);
		code = -1;
		return;
	}
	fprintf(ttyout, "We only support %s structure, sorry.\n", structname);
	code = -1;
}
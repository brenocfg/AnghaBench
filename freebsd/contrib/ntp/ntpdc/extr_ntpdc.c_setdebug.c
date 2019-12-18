#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct parse {scalar_t__ nargs; TYPE_1__* argval; } ;
struct TYPE_2__ {int /*<<< orphan*/  string; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ STREQ (int /*<<< orphan*/ ,char*) ; 
 int debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
setdebug(
	struct parse *pcmd,
	FILE *fp
	)
{
	if (pcmd->nargs == 0) {
		(void) fprintf(fp, "debug level is %d\n", debug);
		return;
	} else if (STREQ(pcmd->argval[0].string, "no")) {
		debug = 0;
	} else if (STREQ(pcmd->argval[0].string, "more")) {
		debug++;
	} else if (STREQ(pcmd->argval[0].string, "less")) {
		debug--;
	} else {
		(void) fprintf(fp, "What?\n");
		return;
	}
	(void) fprintf(fp, "debug level set to %d\n", debug);
}
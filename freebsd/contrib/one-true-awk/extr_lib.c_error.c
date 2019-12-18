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
struct TYPE_2__ {int lineno; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 char** FILENAME ; 
 scalar_t__* FNR ; 
 scalar_t__* NR ; 
 int compile_time ; 
 char* cursource () ; 
 int /*<<< orphan*/  eprint () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int lineno ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 

void error()
{
	extern Node *curnode;

	fprintf(stderr, "\n");
	if (compile_time != 2 && NR && *NR > 0) {
		fprintf(stderr, " input record number %d", (int) (*FNR));
		if (strcmp(*FILENAME, "-") != 0)
			fprintf(stderr, ", file %s", *FILENAME);
		fprintf(stderr, "\n");
	}
	if (compile_time != 2 && curnode)
		fprintf(stderr, " source line number %d", curnode->lineno);
	else if (compile_time != 2 && lineno)
		fprintf(stderr, " source line number %d", lineno);
	if (compile_time == 1 && cursource() != NULL)
		fprintf(stderr, " source file %s", cursource());
	fprintf(stderr, "\n");
	eprint();
}
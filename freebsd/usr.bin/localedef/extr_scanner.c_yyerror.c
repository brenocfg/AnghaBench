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
 int /*<<< orphan*/  exit (int) ; 
 char* filename ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,char const*) ; 
 int lineno ; 
 int /*<<< orphan*/  stderr ; 

void
yyerror(const char *msg)
{
	(void) fprintf(stderr, "%s: %d: error: %s\n",
	    filename, lineno, msg);
	exit(4);
}
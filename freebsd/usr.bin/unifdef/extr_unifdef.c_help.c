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
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  synopsis (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
help(void)
{
	synopsis(stdout);
	printf(
	    "	-Dsym=val  define preprocessor symbol with given value\n"
	    "	-Dsym      define preprocessor symbol with value 1\n"
	    "	-Usym	   preprocessor symbol is undefined\n"
	    "	-iDsym=val \\  ignore C strings and comments\n"
	    "	-iDsym      ) in sections controlled by these\n"
	    "	-iUsym	   /  preprocessor symbols\n"
	    "	-fpath	file containing #define and #undef directives\n"
	    "	-b	blank lines instead of deleting them\n"
	    "	-B	compress blank lines around deleted section\n"
	    "	-c	complement (invert) keep vs. delete\n"
	    "	-d	debugging mode\n"
	    "	-e	ignore multiline preprocessor directives\n"
	    "	-h	print help\n"
	    "	-Ipath	extra include file path (ignored)\n"
	    "	-K	disable && and || short-circuiting\n"
	    "	-k	process constant #if expressions\n"
	    "	-Mext	modify in place and keep backups\n"
	    "	-m	modify input files in place\n"
	    "	-n	add #line directives to output\n"
	    "	-opath	output file name\n"
	    "	-S	list #if control symbols with nesting\n"
	    "	-s	list #if control symbols\n"
	    "	-t	ignore C strings and comments\n"
	    "	-V	print version\n"
	    "	-x{012}	exit status mode\n"
	);
	exit(0);
}
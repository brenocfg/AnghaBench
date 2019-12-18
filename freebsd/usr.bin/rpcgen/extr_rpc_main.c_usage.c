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
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  options_usage () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	f_print(stderr, "%s\n%s\n%s\n%s\n%s\n",
		"usage: rpcgen infile",
		"       rpcgen [-abCLNTM] [-Dname[=value]] [-i size]\
[-I -P [-K seconds]] [-Y path] infile",
		"       rpcgen [-c | -h | -l | -m | -t | -Sc | -Ss | -Sm]\
[-o outfile] [infile]",
		"       rpcgen [-s nettype]* [-o outfile] [infile]",
		"       rpcgen [-n netid]* [-o outfile] [infile]");
	options_usage();
	exit(1);
}
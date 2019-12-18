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
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
options_usage(void)
{
	f_print(stderr, "options:\n");
	f_print(stderr, "-a\t\tgenerate all files, including samples\n");
	f_print(stderr, "-b\t\tbackward compatibility mode (generates code \
for FreeBSD 4.X)\n");
	f_print(stderr, "-c\t\tgenerate XDR routines\n");
	f_print(stderr, "-C\t\tANSI C mode\n");
	f_print(stderr, "-Dname[=value]\tdefine a symbol (same as #define)\n");
	f_print(stderr, "-h\t\tgenerate header file\n");
	f_print(stderr, "-i size\t\tsize at which to start generating\
inline code\n");
	f_print(stderr, "-I\t\tgenerate code for inetd support in server\n");
	f_print(stderr, "-K seconds\tserver exits after K seconds of\
inactivity\n");
	f_print(stderr, "-l\t\tgenerate client side stubs\n");
	f_print(stderr, "-L\t\tserver errors will be printed to syslog\n");
	f_print(stderr, "-m\t\tgenerate server side stubs\n");
	f_print(stderr, "-M\t\tgenerate MT-safe code\n");
	f_print(stderr, "-n netid\tgenerate server code that supports\
named netid\n");
	f_print(stderr, "-N\t\tsupports multiple arguments and\
call-by-value\n");
	f_print(stderr, "-o outfile\tname of the output file\n");
	f_print(stderr, "-P\t\tgenerate code for port monitoring support in server\n");
	f_print(stderr, "-s nettype\tgenerate server code that supports named\
nettype\n");
	f_print(stderr, "-Sc\t\tgenerate sample client code that uses remote\
procedures\n");
	f_print(stderr, "-Ss\t\tgenerate sample server code that defines\
remote procedures\n");
	f_print(stderr, "-Sm \t\tgenerate makefile template \n");

	f_print(stderr, "-t\t\tgenerate RPC dispatch table\n");
	f_print(stderr, "-T\t\tgenerate code to support RPC dispatch tables\n");
	f_print(stderr, "-Y path\t\tpath where cpp is found\n");
	exit(1);
}
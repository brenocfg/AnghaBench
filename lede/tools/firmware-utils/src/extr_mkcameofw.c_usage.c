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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* progname ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 

__attribute__((used)) static void usage(int status)
{
	FILE *stream = (status != EXIT_SUCCESS) ? stderr : stdout;

	fprintf(stream, "Usage: %s [OPTIONS...]\n", progname);
	fprintf(stream,
"\n"
"Options:\n"
"  -k <file>       read kernel image from the file <file>\n"
"  -c              use the kernel image as a combined image\n"
"  -M <model>      set model to <model>\n"
"  -o <file>       write output to the file <file>\n"
"  -r <file>       read rootfs image from the file <file>\n"
"  -S <signature>  set image signature to <signature>\n"
"  -R <region>     set image region to <region>\n"
"  -V <version>    set image version to <version>\n"
"  -I <size>       set image size to <size>\n"
"  -K <size>       set kernel size to <size>\n"
"  -h              show this screen\n"
	);

	exit(status);
}
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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(
      char *program
      )
{
  fprintf(stderr, "usage: %s [-n] [-f] [-l] [-t] [-i] [-o] [-d <drift_file>] [-D <input delay>] <device>\n", program);
	fprintf(stderr, "\t-n              do not change time\n");
	fprintf(stderr, "\t-i              interactive\n");
	fprintf(stderr, "\t-t              trace (print all datagrams)\n");
	fprintf(stderr, "\t-f              print all databits (includes PTB private data)\n");
	fprintf(stderr, "\t-l              print loop filter debug information\n");
	fprintf(stderr, "\t-o              print offet average for current minute\n");
	fprintf(stderr, "\t-Y              make internal Y2K checks then exit\n");	/* Y2KFixes */
	fprintf(stderr, "\t-d <drift_file> specify alternate drift file\n");
	fprintf(stderr, "\t-D <input delay>specify delay from input edge to processing in micro seconds\n");
}
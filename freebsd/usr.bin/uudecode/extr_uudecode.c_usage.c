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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{

	(void)fprintf(stderr,
	    "usage: uudecode [-cimprs] [file ...]\n"
	    "       uudecode [-i] -o output_file [file]\n"
	    "       b64decode [-cimprs] [file ...]\n"
	    "       b64decode [-i] -o output_file [file]\n");
	exit(1);
}
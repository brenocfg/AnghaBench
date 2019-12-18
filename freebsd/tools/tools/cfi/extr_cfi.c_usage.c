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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	fprintf(stderr, "usage: %s [-f device] op...\n", progname);
	fprintf(stderr, "where op's are:\n");
	fprintf(stderr, "fact\t\tread factory PR segment\n");
	fprintf(stderr, "oem\t\tread OEM segment\n");
	fprintf(stderr, "woem value\twrite OEM segment\n");
	fprintf(stderr, "plr\t\tread PLR\n");
	fprintf(stderr, "wplr\t\twrite PLR\n");
	exit(-1);
}
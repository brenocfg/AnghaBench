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

void
usage(void)
{

	fprintf(stderr, "usage: ugidfw add [subject [not] [uid uid] [gid gid]]"
	    " [object [not] [uid uid] \\\n");
	fprintf(stderr, "    [gid gid]] mode arswxn\n");
	fprintf(stderr, "       ugidfw list\n");
	fprintf(stderr, "       ugidfw set rulenum [subject [not] [uid uid] [gid gid]]"
	    " [object [not] \\\n");
	fprintf(stderr, "    [uid uid] [gid gid]] mode arswxn\n");
	fprintf(stderr, "       ugidfw remove rulenum\n");

	exit(1);
}
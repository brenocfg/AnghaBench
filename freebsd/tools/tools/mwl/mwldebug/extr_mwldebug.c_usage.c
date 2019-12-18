#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 TYPE_1__* flags ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	int i;

	fprintf(stderr, "usage: %s [-i device] [flags]\n", progname);
	fprintf(stderr, "where flags are:\n");
	for (i = 0; i < nitems(flags); i++)
		printf("%s\n", flags[i].name);
	exit(-1);
}
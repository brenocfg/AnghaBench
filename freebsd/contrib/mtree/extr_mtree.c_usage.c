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
 unsigned int __arraycount (TYPE_1__*) ; 
 int /*<<< orphan*/  exit (int) ; 
 TYPE_1__* flavors ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* getprogname () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	unsigned int i;

	fprintf(stderr,
	    "usage: %s [-bCcDdejLlMnPqrStUuWx] [-i|-m] [-E tags]\n"
	    "\t\t[-f spec] [-f spec]\n"
	    "\t\t[-I tags] [-K keywords] [-k keywords] [-N dbdir] [-p path]\n"
	    "\t\t[-R keywords] [-s seed] [-X exclude-file]\n"
	    "\t\t[-F flavor]\n",
	    getprogname());
	fprintf(stderr, "\nflavors:");
	for (i = 0; i < __arraycount(flavors); i++)
		fprintf(stderr, " %s", flavors[i].name);
	fprintf(stderr, "\n");
	exit(1);
}
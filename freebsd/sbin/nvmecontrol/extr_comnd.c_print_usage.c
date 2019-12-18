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
struct cmd {char* name; char* descr; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 char* getprogname () ; 
 int /*<<< orphan*/  print_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
print_usage(const struct cmd *f)
{

	fprintf(stderr, "    %s", getprogname());
	print_tree(f->parent);
	fprintf(stderr, " %-15s - %s\n", f->name, f->descr);
}
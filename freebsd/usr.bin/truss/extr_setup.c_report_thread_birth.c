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
struct trussinfo {int /*<<< orphan*/  outfile; struct threadinfo* curthread; } ;
struct threadinfo {scalar_t__ tid; int /*<<< orphan*/  after; int /*<<< orphan*/  before; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  print_line_prefix (struct trussinfo*) ; 

__attribute__((used)) static void
report_thread_birth(struct trussinfo *info)
{
	struct threadinfo *t;

	t = info->curthread;
	clock_gettime(CLOCK_REALTIME, &t->after);
	t->before = t->after;
	print_line_prefix(info);
	fprintf(info->outfile, "<new thread %ld>\n", (long)t->tid);
}
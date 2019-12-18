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
struct xferstat {char* name; void* lastrcvd; void* rcvd; void* offset; void* size; int /*<<< orphan*/  start; int /*<<< orphan*/  last; int /*<<< orphan*/  last2; } ;
typedef  void* off_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct xferstat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  stat_display (struct xferstat*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ v_level ; 
 scalar_t__ v_progress ; 

__attribute__((used)) static void
stat_start(struct xferstat *xs, const char *name, off_t size, off_t offset)
{

	memset(xs, 0, sizeof *xs);
	snprintf(xs->name, sizeof xs->name, "%s", name);
	gettimeofday(&xs->start, NULL);
	xs->last2 = xs->last = xs->start;
	xs->size = size;
	xs->offset = offset;
	xs->rcvd = offset;
	xs->lastrcvd = offset;
	if (v_progress)
		stat_display(xs, 1);
	else if (v_level > 0)
		fprintf(stderr, "%-46s", xs->name);
}
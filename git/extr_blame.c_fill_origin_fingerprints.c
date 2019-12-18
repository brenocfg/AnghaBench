#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fingerprint {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  size; } ;
struct blame_origin {int /*<<< orphan*/  num_lines; TYPE_1__ file; scalar_t__ fingerprints; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_line_starts (int**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  get_line_fingerprints (scalar_t__,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xcalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fill_origin_fingerprints(struct blame_origin *o)
{
	int *line_starts;

	if (o->fingerprints)
		return;
	o->num_lines = find_line_starts(&line_starts, o->file.ptr,
					o->file.size);
	o->fingerprints = xcalloc(sizeof(struct fingerprint), o->num_lines);
	get_line_fingerprints(o->fingerprints, o->file.ptr, line_starts,
			      0, o->num_lines);
	free(line_starts);
}
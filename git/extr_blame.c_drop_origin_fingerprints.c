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
struct blame_origin {scalar_t__ fingerprints; scalar_t__ num_lines; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (scalar_t__) ; 
 int /*<<< orphan*/  free_line_fingerprints (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void drop_origin_fingerprints(struct blame_origin *o)
{
	if (o->fingerprints) {
		free_line_fingerprints(o->fingerprints, o->num_lines);
		o->num_lines = 0;
		FREE_AND_NULL(o->fingerprints);
	}
}
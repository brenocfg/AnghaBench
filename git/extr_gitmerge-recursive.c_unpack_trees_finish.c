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
struct merge_options {int /*<<< orphan*/  unpack_opts; int /*<<< orphan*/  orig_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_unpack_trees_porcelain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  discard_index (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unpack_trees_finish(struct merge_options *o)
{
	discard_index(&o->orig_index);
	clear_unpack_trees_porcelain(&o->unpack_opts);
}
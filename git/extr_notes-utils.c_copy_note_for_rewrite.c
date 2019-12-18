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
struct object_id {int dummy; } ;
struct notes_rewrite_cfg {int /*<<< orphan*/  combine; scalar_t__* trees; } ;

/* Variables and functions */
 scalar_t__ copy_note (scalar_t__,struct object_id const*,struct object_id const*,int,int /*<<< orphan*/ ) ; 

int copy_note_for_rewrite(struct notes_rewrite_cfg *c,
			  const struct object_id *from_obj, const struct object_id *to_obj)
{
	int ret = 0;
	int i;
	for (i = 0; c->trees[i]; i++)
		ret = copy_note(c->trees[i], from_obj, to_obj, 1, c->combine) || ret;
	return ret;
}
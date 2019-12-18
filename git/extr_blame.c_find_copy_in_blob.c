#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct handle_split_cb_data {scalar_t__ num_lines; int /*<<< orphan*/  plno; int /*<<< orphan*/  tlno; scalar_t__ lno; struct handle_split_cb_data* split; struct blame_origin* parent; struct handle_split_cb_data* ent; struct blame_scoreboard* sb; } ;
struct blame_scoreboard {int /*<<< orphan*/  xdl_opts; } ;
struct blame_origin {TYPE_2__* commit; } ;
struct blame_entry {scalar_t__ num_lines; int /*<<< orphan*/  plno; int /*<<< orphan*/  tlno; scalar_t__ lno; struct blame_entry* split; struct blame_origin* parent; struct blame_entry* ent; struct blame_scoreboard* sb; } ;
struct TYPE_9__ {char* ptr; int size; } ;
typedef  TYPE_3__ mmfile_t ;
typedef  int /*<<< orphan*/  d ;
struct TYPE_7__ {int /*<<< orphan*/  oid; } ;
struct TYPE_8__ {TYPE_1__ object; } ;

/* Variables and functions */
 char const* blame_nth_line (struct blame_scoreboard*,scalar_t__) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ diff_hunks (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ,struct handle_split_cb_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_split (struct blame_scoreboard*,struct handle_split_cb_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct blame_origin*,struct handle_split_cb_data*) ; 
 int /*<<< orphan*/  handle_split_cb ; 
 int /*<<< orphan*/  memset (struct handle_split_cb_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void find_copy_in_blob(struct blame_scoreboard *sb,
			      struct blame_entry *ent,
			      struct blame_origin *parent,
			      struct blame_entry *split,
			      mmfile_t *file_p)
{
	const char *cp;
	mmfile_t file_o;
	struct handle_split_cb_data d;

	memset(&d, 0, sizeof(d));
	d.sb = sb; d.ent = ent; d.parent = parent; d.split = split;
	/*
	 * Prepare mmfile that contains only the lines in ent.
	 */
	cp = blame_nth_line(sb, ent->lno);
	file_o.ptr = (char *) cp;
	file_o.size = blame_nth_line(sb, ent->lno + ent->num_lines) - cp;

	/*
	 * file_o is a part of final image we are annotating.
	 * file_p partially may match that image.
	 */
	memset(split, 0, sizeof(struct blame_entry [3]));
	if (diff_hunks(file_p, &file_o, handle_split_cb, &d, sb->xdl_opts))
		die("unable to generate diff (%s)",
		    oid_to_hex(&parent->commit->object.oid));
	/* remainder, if any, all match the preimage */
	handle_split(sb, ent, d.tlno, d.plno, ent->num_lines, parent, split);
}
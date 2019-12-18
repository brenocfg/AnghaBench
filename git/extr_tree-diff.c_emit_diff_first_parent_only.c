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
struct diff_options {int /*<<< orphan*/  (* add_remove ) (struct diff_options*,int,unsigned int,struct object_id const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* change ) (struct diff_options*,unsigned int,int,struct object_id*,struct object_id*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct combine_diff_path {int mode; int /*<<< orphan*/  path; struct object_id oid; struct combine_diff_parent* parent; } ;
struct combine_diff_parent {unsigned int mode; struct object_id oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct diff_options*,unsigned int,int,struct object_id*,struct object_id*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct diff_options*,int,unsigned int,struct object_id const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emit_diff_first_parent_only(struct diff_options *opt, struct combine_diff_path *p)
{
	struct combine_diff_parent *p0 = &p->parent[0];
	if (p->mode && p0->mode) {
		opt->change(opt, p0->mode, p->mode, &p0->oid, &p->oid,
			1, 1, p->path, 0, 0);
	}
	else {
		const struct object_id *oid;
		unsigned int mode;
		int addremove;

		if (p->mode) {
			addremove = '+';
			oid = &p->oid;
			mode = p->mode;
		} else {
			addremove = '-';
			oid = &p0->oid;
			mode = p0->mode;
		}

		opt->add_remove(opt, addremove, mode, oid, 1, p->path, 0);
	}

	return 0;	/* we are done with p */
}
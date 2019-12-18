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
struct strbuf {char const* buf; scalar_t__ len; } ;
struct rev_info {int /*<<< orphan*/  pending; scalar_t__ reflog_info; scalar_t__ no_walk; } ;
struct object {int flags; scalar_t__ type; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 scalar_t__ OBJ_COMMIT ; 
 struct strbuf STRBUF_INIT ; 
 int UNINTERESTING ; 
 int /*<<< orphan*/  add_object_array_with_path (struct object*,char const*,int /*<<< orphan*/ *,unsigned int,char const*) ; 
 int /*<<< orphan*/  add_reflog_for_walk (scalar_t__,struct commit*,char const*) ; 
 int interpret_branch_name (char const*,int /*<<< orphan*/ ,struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void add_pending_object_with_path(struct rev_info *revs,
					 struct object *obj,
					 const char *name, unsigned mode,
					 const char *path)
{
	if (!obj)
		return;
	if (revs->no_walk && (obj->flags & UNINTERESTING))
		revs->no_walk = 0;
	if (revs->reflog_info && obj->type == OBJ_COMMIT) {
		struct strbuf buf = STRBUF_INIT;
		int len = interpret_branch_name(name, 0, &buf, 0);

		if (0 < len && name[len] && buf.len)
			strbuf_addstr(&buf, name + len);
		add_reflog_for_walk(revs->reflog_info,
				    (struct commit *)obj,
				    buf.buf[0] ? buf.buf: name);
		strbuf_release(&buf);
		return; /* do not add the commit itself */
	}
	add_object_array_with_path(obj, name, &revs->pending, mode, path);
}
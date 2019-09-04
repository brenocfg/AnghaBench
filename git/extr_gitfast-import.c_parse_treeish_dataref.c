#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct object_id {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct object_entry {scalar_t__ type; TYPE_1__ idx; } ;
struct TYPE_4__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 scalar_t__ OBJ_TREE ; 
 TYPE_2__ command_buf ; 
 struct object_entry* dereference (struct object_entry*,struct object_id*) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 struct object_entry* find_mark (int /*<<< orphan*/ ) ; 
 struct object_entry* find_object (struct object_id*) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_mark_ref_space (char const**) ; 
 scalar_t__ parse_oid_hex (char const*,struct object_id*,char const**) ; 

__attribute__((used)) static struct object_entry *parse_treeish_dataref(const char **p)
{
	struct object_id oid;
	struct object_entry *e;

	if (**p == ':') {	/* <mark> */
		e = find_mark(parse_mark_ref_space(p));
		if (!e)
			die("Unknown mark: %s", command_buf.buf);
		oidcpy(&oid, &e->idx.oid);
	} else {	/* <sha1> */
		if (parse_oid_hex(*p, &oid, p))
			die("Invalid dataref: %s", command_buf.buf);
		e = find_object(&oid);
		if (*(*p)++ != ' ')
			die("Missing space after tree-ish: %s", command_buf.buf);
	}

	while (!e || e->type != OBJ_TREE)
		e = dereference(e, &oid);
	return e;
}
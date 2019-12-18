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
struct object_id {int dummy; } ;
struct object_array {int dummy; } ;
struct object {scalar_t__ type; int flags; } ;
struct child_process {int /*<<< orphan*/  out; } ;
struct TYPE_2__ {unsigned int hexsz; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  GIT_MAX_HEXSZ ; 
 scalar_t__ OBJ_COMMIT ; 
 int TMP_MARK ; 
 int /*<<< orphan*/  add_object_array (struct object*,int /*<<< orphan*/ *,struct object_array*) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 scalar_t__ do_reachable_revlist (struct child_process*,struct object_array*,struct object_array*) ; 
 scalar_t__ finish_command (struct child_process*) ; 
 struct object* get_indexed_object (int) ; 
 int get_max_object_index () ; 
 struct object* lookup_object (int /*<<< orphan*/ ,struct object_id*) ; 
 scalar_t__ parse_oid_hex (char*,struct object_id*,char const**) ; 
 int read_in_full (int /*<<< orphan*/ ,char*,unsigned int const) ; 
 TYPE_1__* the_hash_algo ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int get_reachable_list(struct object_array *src,
			      struct object_array *reachable)
{
	struct child_process cmd = CHILD_PROCESS_INIT;
	int i;
	struct object *o;
	char namebuf[GIT_MAX_HEXSZ + 2]; /* ^ + hash + LF */
	const unsigned hexsz = the_hash_algo->hexsz;

	if (do_reachable_revlist(&cmd, src, reachable) < 0)
		return -1;

	while ((i = read_in_full(cmd.out, namebuf, hexsz + 1)) == hexsz + 1) {
		struct object_id oid;
		const char *p;

		if (parse_oid_hex(namebuf, &oid, &p) || *p != '\n')
			break;

		o = lookup_object(the_repository, &oid);
		if (o && o->type == OBJ_COMMIT) {
			o->flags &= ~TMP_MARK;
		}
	}
	for (i = get_max_object_index(); 0 < i; i--) {
		o = get_indexed_object(i - 1);
		if (o && o->type == OBJ_COMMIT &&
		    (o->flags & TMP_MARK)) {
			add_object_array(o, NULL, reachable);
				o->flags &= ~TMP_MARK;
		}
	}
	close(cmd.out);

	if (finish_command(&cmd))
		return -1;

	return 0;
}
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
struct object {scalar_t__ type; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int ADVERTISED ; 
 int COMMON ; 
 scalar_t__ OBJ_COMMIT ; 
 int POPPED ; 
 int SEEN ; 
 int /*<<< orphan*/  clear_commit_marks (struct commit*,int) ; 
 struct object* deref_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int clear_marks(const char *refname, const struct object_id *oid,
		       int flag, void *cb_data)
{
	struct object *o = deref_tag(the_repository, parse_object(the_repository, oid), refname, 0);

	if (o && o->type == OBJ_COMMIT)
		clear_commit_marks((struct commit *)o,
				   COMMON | ADVERTISED | SEEN | POPPED);
	return 0;
}
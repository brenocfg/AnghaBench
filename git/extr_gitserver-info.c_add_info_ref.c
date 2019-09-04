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
struct object {scalar_t__ type; struct object_id const oid; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ OBJ_TAG ; 
 struct object* deref_tag (int /*<<< orphan*/ ,struct object*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,char*,char const*) ; 
 char* oid_to_hex (struct object_id const*) ; 
 struct object* parse_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int add_info_ref(const char *path, const struct object_id *oid,
			int flag, void *cb_data)
{
	FILE *fp = cb_data;
	struct object *o = parse_object(the_repository, oid);
	if (!o)
		return -1;

	if (fprintf(fp, "%s	%s\n", oid_to_hex(oid), path) < 0)
		return -1;

	if (o->type == OBJ_TAG) {
		o = deref_tag(the_repository, o, path, 0);
		if (o)
			if (fprintf(fp, "%s	%s^{}\n",
				oid_to_hex(&o->oid), path) < 0)
				return -1;
	}
	return 0;
}
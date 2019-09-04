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
struct tag {TYPE_1__* tagged; int /*<<< orphan*/  tag; } ;
struct object {int dummy; } ;
struct atom_value {void* s; } ;
struct TYPE_4__ {char* name; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  type_name (int /*<<< orphan*/ ) ; 
 TYPE_2__* used_atom ; 
 int used_atom_cnt ; 
 void* xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void grab_tag_values(struct atom_value *val, int deref, struct object *obj)
{
	int i;
	struct tag *tag = (struct tag *) obj;

	for (i = 0; i < used_atom_cnt; i++) {
		const char *name = used_atom[i].name;
		struct atom_value *v = &val[i];
		if (!!deref != (*name == '*'))
			continue;
		if (deref)
			name++;
		if (!strcmp(name, "tag"))
			v->s = xstrdup(tag->tag);
		else if (!strcmp(name, "type") && tag->tagged)
			v->s = xstrdup(type_name(tag->tagged->type));
		else if (!strcmp(name, "object") && tag->tagged)
			v->s = xstrdup(oid_to_hex(&tag->tagged->oid));
	}
}
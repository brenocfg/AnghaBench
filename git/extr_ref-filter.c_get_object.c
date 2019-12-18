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
struct strbuf {int dummy; } ;
struct ref_array_item {int /*<<< orphan*/  value; int /*<<< orphan*/  refname; } ;
struct object {int dummy; } ;
struct TYPE_2__ {scalar_t__ contentp; scalar_t__ disk_sizep; int /*<<< orphan*/ * typep; int /*<<< orphan*/ * sizep; } ;
struct expand_data {scalar_t__ disk_size; int /*<<< orphan*/  content; int /*<<< orphan*/  oid; int /*<<< orphan*/  size; int /*<<< orphan*/  type; TYPE_1__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  OBJECT_INFO_LOOKUP_REPLACE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grab_common_values (int /*<<< orphan*/ ,int,struct expand_data*) ; 
 int /*<<< orphan*/  grab_values (int /*<<< orphan*/ ,int,struct object*,int /*<<< orphan*/ ) ; 
 scalar_t__ oid_object_info_extended (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 struct object* parse_object_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int strbuf_addf_ret (struct strbuf*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int get_object(struct ref_array_item *ref, int deref, struct object **obj,
		      struct expand_data *oi, struct strbuf *err)
{
	/* parse_object_buffer() will set eaten to 0 if free() will be needed */
	int eaten = 1;
	if (oi->info.contentp) {
		/* We need to know that to use parse_object_buffer properly */
		oi->info.sizep = &oi->size;
		oi->info.typep = &oi->type;
	}
	if (oid_object_info_extended(the_repository, &oi->oid, &oi->info,
				     OBJECT_INFO_LOOKUP_REPLACE))
		return strbuf_addf_ret(err, -1, _("missing object %s for %s"),
				       oid_to_hex(&oi->oid), ref->refname);
	if (oi->info.disk_sizep && oi->disk_size < 0)
		BUG("Object size is less than zero.");

	if (oi->info.contentp) {
		*obj = parse_object_buffer(the_repository, &oi->oid, oi->type, oi->size, oi->content, &eaten);
		if (!obj) {
			if (!eaten)
				free(oi->content);
			return strbuf_addf_ret(err, -1, _("parse_object_buffer failed on %s for %s"),
					       oid_to_hex(&oi->oid), ref->refname);
		}
		grab_values(ref->value, deref, *obj, oi->content);
	}

	grab_common_values(ref->value, deref, oi);
	if (!eaten)
		free(oi->content);
	return 0;
}
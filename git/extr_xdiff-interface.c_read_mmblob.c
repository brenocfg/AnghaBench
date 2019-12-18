#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct object_id {int dummy; } ;
struct TYPE_3__ {unsigned long size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ mmfile_t ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int OBJ_BLOB ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_oid ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 scalar_t__ oideq (struct object_id const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_object_file (struct object_id const*,int*,unsigned long*) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

void read_mmblob(mmfile_t *ptr, const struct object_id *oid)
{
	unsigned long size;
	enum object_type type;

	if (oideq(oid, &null_oid)) {
		ptr->ptr = xstrdup("");
		ptr->size = 0;
		return;
	}

	ptr->ptr = read_object_file(oid, &type, &size);
	if (!ptr->ptr || type != OBJ_BLOB)
		die("unable to read blob object %s", oid_to_hex(oid));
	ptr->size = size;
}
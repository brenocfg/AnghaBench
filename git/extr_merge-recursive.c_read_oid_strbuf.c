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
struct strbuf {int dummy; } ;
struct object_id {int dummy; } ;
struct merge_options {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int OBJ_BLOB ; 
 int /*<<< orphan*/  _ (char*) ; 
 int err (struct merge_options*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 void* read_object_file (struct object_id const*,int*,unsigned long*) ; 
 int /*<<< orphan*/  strbuf_attach (struct strbuf*,void*,unsigned long,unsigned long) ; 

__attribute__((used)) static int read_oid_strbuf(struct merge_options *opt,
			   const struct object_id *oid,
			   struct strbuf *dst)
{
	void *buf;
	enum object_type type;
	unsigned long size;
	buf = read_object_file(oid, &type, &size);
	if (!buf)
		return err(opt, _("cannot read object %s"), oid_to_hex(oid));
	if (type != OBJ_BLOB) {
		free(buf);
		return err(opt, _("object %s is not a blob"), oid_to_hex(oid));
	}
	strbuf_attach(dst, buf, size, size + 1);
	return 0;
}
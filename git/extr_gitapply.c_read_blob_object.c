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
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 scalar_t__ S_ISGITLINK (unsigned int) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 char* read_object_file (struct object_id const*,int*,unsigned long*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_attach (struct strbuf*,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,int) ; 

__attribute__((used)) static int read_blob_object(struct strbuf *buf, const struct object_id *oid, unsigned mode)
{
	if (S_ISGITLINK(mode)) {
		strbuf_grow(buf, 100);
		strbuf_addf(buf, "Subproject commit %s\n", oid_to_hex(oid));
	} else {
		enum object_type type;
		unsigned long sz;
		char *result;

		result = read_object_file(oid, &type, &sz);
		if (!result)
			return -1;
		/* XXX read_sha1_file NUL-terminates */
		strbuf_attach(buf, result, sz, sz + 1);
	}
	return 0;
}
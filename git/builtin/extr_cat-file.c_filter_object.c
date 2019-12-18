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
struct strbuf {unsigned long len; } ;
struct object_id {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int OBJ_BLOB ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ S_ISREG (unsigned int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ convert_to_working_tree (int /*<<< orphan*/ *,char const*,char*,unsigned long,struct strbuf*) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 char* read_object_file (struct object_id const*,int*,unsigned long*) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_index ; 

__attribute__((used)) static int filter_object(const char *path, unsigned mode,
			 const struct object_id *oid,
			 char **buf, unsigned long *size)
{
	enum object_type type;

	*buf = read_object_file(oid, &type, size);
	if (!*buf)
		return error(_("cannot read object %s '%s'"),
			     oid_to_hex(oid), path);
	if ((type == OBJ_BLOB) && S_ISREG(mode)) {
		struct strbuf strbuf = STRBUF_INIT;
		if (convert_to_working_tree(&the_index, path, *buf, *size, &strbuf)) {
			free(*buf);
			*size = strbuf.len;
			*buf = strbuf_detach(&strbuf, NULL);
		}
	}

	return 0;
}
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
struct index_state {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 unsigned int HASH_FORMAT_CHECK ; 
 unsigned int HASH_WRITE_OBJECT ; 
 int OBJ_BLOB ; 
 int OBJ_COMMIT ; 
 int OBJ_TAG ; 
 int OBJ_TREE ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  check_commit (void*,size_t) ; 
 int /*<<< orphan*/  check_tag (void*,size_t) ; 
 int /*<<< orphan*/  check_tree (void*,size_t) ; 
 scalar_t__ convert_to_git (struct index_state*,char const*,void*,size_t,struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  get_conv_flags (unsigned int) ; 
 int hash_object_file (void*,size_t,int /*<<< orphan*/ ,struct object_id*) ; 
 void* strbuf_detach (struct strbuf*,size_t*) ; 
 int /*<<< orphan*/  type_name (int) ; 
 int write_object_file (void*,size_t,int /*<<< orphan*/ ,struct object_id*) ; 

__attribute__((used)) static int index_mem(struct index_state *istate,
		     struct object_id *oid, void *buf, size_t size,
		     enum object_type type,
		     const char *path, unsigned flags)
{
	int ret, re_allocated = 0;
	int write_object = flags & HASH_WRITE_OBJECT;

	if (!type)
		type = OBJ_BLOB;

	/*
	 * Convert blobs to git internal format
	 */
	if ((type == OBJ_BLOB) && path) {
		struct strbuf nbuf = STRBUF_INIT;
		if (convert_to_git(istate, path, buf, size, &nbuf,
				   get_conv_flags(flags))) {
			buf = strbuf_detach(&nbuf, &size);
			re_allocated = 1;
		}
	}
	if (flags & HASH_FORMAT_CHECK) {
		if (type == OBJ_TREE)
			check_tree(buf, size);
		if (type == OBJ_COMMIT)
			check_commit(buf, size);
		if (type == OBJ_TAG)
			check_tag(buf, size);
	}

	if (write_object)
		ret = write_object_file(buf, size, type_name(type), oid);
	else
		ret = hash_object_file(buf, size, type_name(type), oid);
	if (re_allocated)
		free(buf);
	return ret;
}
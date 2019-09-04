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
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int OBJ_COMMIT ; 
 int error (char*,char const*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 char* read_object_file (struct object_id*,int*,unsigned long*) ; 
 int run_gpg_verify (struct object_id*,char*,unsigned long,unsigned int) ; 
 char* type_name (int) ; 

__attribute__((used)) static int verify_commit(const char *name, unsigned flags)
{
	enum object_type type;
	struct object_id oid;
	char *buf;
	unsigned long size;
	int ret;

	if (get_oid(name, &oid))
		return error("commit '%s' not found.", name);

	buf = read_object_file(&oid, &type, &size);
	if (!buf)
		return error("%s: unable to read file.", name);
	if (type != OBJ_COMMIT)
		return error("%s: cannot verify a non-commit object of type %s.",
				name, type_name(type));

	ret = run_gpg_verify(&oid, buf, size, flags);

	free(buf);
	return ret;
}
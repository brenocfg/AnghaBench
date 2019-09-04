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
 int check_object_signature (struct object_id const*,void*,unsigned long,char const*) ; 
 int /*<<< orphan*/  free (void*) ; 
 struct object_id* lookup_replace_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 void* read_object_file (struct object_id const*,int*,unsigned long*) ; 
 int /*<<< orphan*/  the_repository ; 
 int type_from_string (char const*) ; 

__attribute__((used)) static int verify_object(const struct object_id *oid, const char *expected_type)
{
	int ret = -1;
	enum object_type type;
	unsigned long size;
	void *buffer = read_object_file(oid, &type, &size);
	const struct object_id *repl = lookup_replace_object(the_repository, oid);

	if (buffer) {
		if (type == type_from_string(expected_type))
			ret = check_object_signature(repl, buffer, size, expected_type);
		free(buffer);
	}
	return ret;
}
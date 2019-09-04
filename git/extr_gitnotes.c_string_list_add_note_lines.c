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
struct string_list {int dummy; } ;
struct object_id {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int OBJ_BLOB ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_null_oid (struct object_id const*) ; 
 char* read_object_file (struct object_id const*,int*,unsigned long*) ; 
 int /*<<< orphan*/  string_list_split (struct string_list*,char*,char,int) ; 

__attribute__((used)) static int string_list_add_note_lines(struct string_list *list,
				      const struct object_id *oid)
{
	char *data;
	unsigned long len;
	enum object_type t;

	if (is_null_oid(oid))
		return 0;

	/* read_sha1_file NUL-terminates */
	data = read_object_file(oid, &t, &len);
	if (t != OBJ_BLOB || !data || !len) {
		free(data);
		return t != OBJ_BLOB || !data;
	}

	/*
	 * If the last line of the file is EOL-terminated, this will
	 * add an empty string to the list.  But it will be removed
	 * later, along with any empty strings that came from empty
	 * lines within the file.
	 */
	string_list_split(list, data, '\n', -1);
	free(data);
	return 0;
}
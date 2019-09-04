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
struct notes_cache {int /*<<< orphan*/  tree; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 struct object_id* get_note (int /*<<< orphan*/ *,struct object_id*) ; 
 char* read_object_file (struct object_id const*,int*,unsigned long*) ; 

char *notes_cache_get(struct notes_cache *c, struct object_id *key_oid,
		      size_t *outsize)
{
	const struct object_id *value_oid;
	enum object_type type;
	char *value;
	unsigned long size;

	value_oid = get_note(&c->tree, key_oid);
	if (!value_oid)
		return NULL;
	value = read_object_file(value_oid, &type, &size);

	*outsize = size;
	return value;
}
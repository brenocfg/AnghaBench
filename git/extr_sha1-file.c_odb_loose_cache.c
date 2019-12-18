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
struct oid_array {int dummy; } ;
struct object_id {int* hash; } ;
struct object_directory {int* loose_objects_subdir_seen; struct oid_array* loose_objects_cache; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  BUG (char*) ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  append_loose_object ; 
 int /*<<< orphan*/  for_each_file_in_obj_subdir (int,struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct oid_array*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

struct oid_array *odb_loose_cache(struct object_directory *odb,
				  const struct object_id *oid)
{
	int subdir_nr = oid->hash[0];
	struct strbuf buf = STRBUF_INIT;

	if (subdir_nr < 0 ||
	    subdir_nr >= ARRAY_SIZE(odb->loose_objects_subdir_seen))
		BUG("subdir_nr out of range");

	if (odb->loose_objects_subdir_seen[subdir_nr])
		return &odb->loose_objects_cache[subdir_nr];

	strbuf_addstr(&buf, odb->path);
	for_each_file_in_obj_subdir(subdir_nr, &buf,
				    append_loose_object,
				    NULL, NULL,
				    &odb->loose_objects_cache[subdir_nr]);
	odb->loose_objects_subdir_seen[subdir_nr] = 1;
	strbuf_release(&buf);
	return &odb->loose_objects_cache[subdir_nr];
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct object_entry {unsigned long size; scalar_t__ type; TYPE_1__ idx; } ;
struct compare_data {int /*<<< orphan*/  buf; int /*<<< orphan*/  st; struct object_entry* entry; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 scalar_t__ OBJ_BLOB ; 
 int /*<<< orphan*/  _ (char*) ; 
 unsigned long big_file_threshold ; 
 int /*<<< orphan*/  close_istream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare_objects ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct compare_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_istream (int /*<<< orphan*/ *,int*,unsigned long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unpack_data (struct object_entry*,int /*<<< orphan*/ ,struct compare_data*) ; 

__attribute__((used)) static int check_collison(struct object_entry *entry)
{
	struct compare_data data;
	enum object_type type;
	unsigned long size;

	if (entry->size <= big_file_threshold || entry->type != OBJ_BLOB)
		return -1;

	memset(&data, 0, sizeof(data));
	data.entry = entry;
	data.st = open_istream(&entry->idx.oid, &type, &size, NULL);
	if (!data.st)
		return -1;
	if (size != entry->size || type != entry->type)
		die(_("SHA1 COLLISION FOUND WITH %s !"),
		    oid_to_hex(&entry->idx.oid));
	unpack_data(entry, compare_objects, &data);
	close_istream(data.st);
	free(data.buf);
	return 0;
}
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
struct cache_entry {int /*<<< orphan*/  oid; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int OBJ_BLOB ; 
 int /*<<< orphan*/  free (void*) ; 
 void* read_object_file (int /*<<< orphan*/ *,int*,unsigned long*) ; 

__attribute__((used)) static void *read_blob_entry(const struct cache_entry *ce, unsigned long *size)
{
	enum object_type type;
	void *blob_data = read_object_file(&ce->oid, &type, size);

	if (blob_data) {
		if (type == OBJ_BLOB)
			return blob_data;
		free(blob_data);
	}
	return NULL;
}
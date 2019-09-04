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
struct object_directory {int /*<<< orphan*/  loose_objects_subdir_seen; int /*<<< orphan*/ * loose_objects_cache; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oid_array_clear (int /*<<< orphan*/ *) ; 

void odb_clear_loose_cache(struct object_directory *odb)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(odb->loose_objects_cache); i++)
		oid_array_clear(&odb->loose_objects_cache[i]);
	memset(&odb->loose_objects_subdir_seen, 0,
	       sizeof(odb->loose_objects_subdir_seen));
}
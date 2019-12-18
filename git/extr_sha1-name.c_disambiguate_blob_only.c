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
struct repository {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int OBJ_BLOB ; 
 int oid_object_info (struct repository*,struct object_id const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int disambiguate_blob_only(struct repository *r,
				  const struct object_id *oid,
				  void *cb_data_unused)
{
	int kind = oid_object_info(r, oid, NULL);
	return kind == OBJ_BLOB;
}
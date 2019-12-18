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
struct object_info {int* typep; unsigned long* sizep; } ;
struct object_id {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 struct object_info OBJECT_INFO_INIT ; 
 int /*<<< orphan*/  OBJECT_INFO_LOOKUP_REPLACE ; 
 scalar_t__ oid_object_info_extended (struct repository*,struct object_id const*,struct object_info*,int /*<<< orphan*/ ) ; 

int oid_object_info(struct repository *r,
		    const struct object_id *oid,
		    unsigned long *sizep)
{
	enum object_type type;
	struct object_info oi = OBJECT_INFO_INIT;

	oi.typep = &type;
	oi.sizep = sizep;
	if (oid_object_info_extended(r, oid, &oi,
				      OBJECT_INFO_LOOKUP_REPLACE) < 0)
		return -1;
	return type;
}
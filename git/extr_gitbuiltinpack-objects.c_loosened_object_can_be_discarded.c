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
typedef  scalar_t__ timestamp_t ;
struct object_id {int dummy; } ;

/* Variables and functions */
 scalar_t__ oid_array_lookup (int /*<<< orphan*/ *,struct object_id const*) ; 
 int /*<<< orphan*/  recent_objects ; 
 scalar_t__ unpack_unreachable_expiration ; 

__attribute__((used)) static int loosened_object_can_be_discarded(const struct object_id *oid,
					    timestamp_t mtime)
{
	if (!unpack_unreachable_expiration)
		return 0;
	if (mtime > unpack_unreachable_expiration)
		return 0;
	if (oid_array_lookup(&recent_objects, oid) >= 0)
		return 0;
	return 1;
}
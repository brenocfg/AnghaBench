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
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  have_repository; } ;

/* Variables and functions */
 int OBJECT_INFO_SKIP_CACHED ; 
 scalar_t__ oid_object_info_extended (struct repository*,struct object_id const*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* startup_info ; 

int repo_has_object_file_with_flags(struct repository *r,
				    const struct object_id *oid, int flags)
{
	if (!startup_info->have_repository)
		return 0;
	return oid_object_info_extended(r, oid, NULL,
					flags | OBJECT_INFO_SKIP_CACHED) >= 0;
}
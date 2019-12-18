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
struct pt_version {int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT_VERSION_BUILD ; 
 int /*<<< orphan*/  PT_VERSION_EXT ; 
 int /*<<< orphan*/  PT_VERSION_MAJOR ; 
 int /*<<< orphan*/  PT_VERSION_MINOR ; 
 int /*<<< orphan*/  PT_VERSION_PATCH ; 

struct pt_version pt_library_version(void)
{
	struct pt_version v = {
		/* .major = */ PT_VERSION_MAJOR,
		/* .minor = */ PT_VERSION_MINOR,
		/* .patch = */ PT_VERSION_PATCH,
		/* .build = */ PT_VERSION_BUILD,
		/* .ext = */ PT_VERSION_EXT
	};

	return v;
}
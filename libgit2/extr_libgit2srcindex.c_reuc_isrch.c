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
struct TYPE_2__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_reuc_entry ;

/* Variables and functions */
 int strcasecmp (void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reuc_isrch(const void *key, const void *array_member)
{
	const git_index_reuc_entry *reuc = array_member;

	return strcasecmp(key, reuc->path);
}
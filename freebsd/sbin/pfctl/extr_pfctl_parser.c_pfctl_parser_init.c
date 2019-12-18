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

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ hcreate_r (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isgroup_map ; 

__attribute__((used)) static __attribute__((constructor)) void
pfctl_parser_init(void)
{
	/*
	 * As hdestroy() will never be called on these tables, it will be
	 * safe to use references into the stored data as keys.
	 */
	if (hcreate_r(0, &isgroup_map) == 0)
		err(1, "Failed to create interface group query response map");
}
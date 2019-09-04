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
struct remote_island {int dummy; } ;
typedef  scalar_t__ khiter_t ;

/* Variables and functions */
 scalar_t__ core_island_name ; 
 scalar_t__ kh_end (int /*<<< orphan*/ ) ; 
 scalar_t__ kh_get_str (int /*<<< orphan*/ ,scalar_t__) ; 
 struct remote_island* kh_value (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  remote_islands ; 

__attribute__((used)) static struct remote_island *get_core_island(void)
{
	if (core_island_name) {
		khiter_t pos = kh_get_str(remote_islands, core_island_name);
		if (pos < kh_end(remote_islands))
			return kh_value(remote_islands, pos);
	}

	return NULL;
}
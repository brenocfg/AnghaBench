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
struct packed_git {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_delta_base_cache_entry (struct packed_git*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int in_delta_base_cache(struct packed_git *p, off_t base_offset)
{
	return !!get_delta_base_cache_entry(p, base_offset);
}
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
struct index_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  untracked_cache_invalidate_path (struct index_state*,char const*,int) ; 

void untracked_cache_add_to_index(struct index_state *istate,
				  const char *path)
{
	untracked_cache_invalidate_path(istate, path, 1);
}
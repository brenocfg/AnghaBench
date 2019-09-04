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
struct cache_entry {int dummy; } ;

/* Variables and functions */
 struct cache_entry* refresh_cache_ent (struct index_state*,struct cache_entry*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct cache_entry *refresh_cache_entry(struct index_state *istate,
					struct cache_entry *ce,
					unsigned int options)
{
	return refresh_cache_ent(istate, ce, options, NULL, NULL);
}
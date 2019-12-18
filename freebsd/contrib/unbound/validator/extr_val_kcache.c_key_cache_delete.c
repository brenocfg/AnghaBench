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
struct key_cache {int /*<<< orphan*/  slab; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct key_cache*) ; 
 int /*<<< orphan*/  slabhash_delete (int /*<<< orphan*/ ) ; 

void 
key_cache_delete(struct key_cache* kcache)
{
	if(!kcache)
		return;
	slabhash_delete(kcache->slab);
	free(kcache);
}
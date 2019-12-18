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
 size_t slabhash_get_mem (int /*<<< orphan*/ ) ; 

size_t 
key_cache_get_mem(struct key_cache* kcache)
{
	return sizeof(*kcache) + slabhash_get_mem(kcache->slab);
}
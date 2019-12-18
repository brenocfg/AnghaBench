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
struct submodule_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct submodule_cache*) ; 
 int /*<<< orphan*/  submodule_cache_clear (struct submodule_cache*) ; 

void submodule_cache_free(struct submodule_cache *cache)
{
	submodule_cache_clear(cache);
	free(cache);
}
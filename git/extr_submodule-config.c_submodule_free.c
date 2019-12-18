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
struct repository {scalar_t__ submodule_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  submodule_cache_clear (scalar_t__) ; 

void submodule_free(struct repository *r)
{
	if (r->submodule_cache)
		submodule_cache_clear(r->submodule_cache);
}
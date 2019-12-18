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
struct nl_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL_DBG (int,char*,struct nl_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct nl_cache*) ; 
 int /*<<< orphan*/  nl_cache_clear (struct nl_cache*) ; 
 int /*<<< orphan*/  nl_cache_name (struct nl_cache*) ; 

void nl_cache_free(struct nl_cache *cache)
{
	if (!cache)
		return;

	nl_cache_clear(cache);
	NL_DBG(1, "Freeing cache %p <%s>...\n", cache, nl_cache_name(cache));
	free(cache);
}
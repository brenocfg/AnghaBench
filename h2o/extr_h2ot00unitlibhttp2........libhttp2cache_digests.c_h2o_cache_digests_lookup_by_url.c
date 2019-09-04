#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  complete; int /*<<< orphan*/  url_only; } ;
struct TYPE_5__ {TYPE_1__ fresh; } ;
typedef  TYPE_2__ h2o_cache_digests_t ;
typedef  int /*<<< orphan*/  h2o_cache_digests_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  lookup (int /*<<< orphan*/ *,char const*,size_t,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

h2o_cache_digests_state_t h2o_cache_digests_lookup_by_url(h2o_cache_digests_t *digests, const char *url, size_t url_len)
{
    return lookup(&digests->fresh.url_only, url, url_len, "", 0, 1, digests->fresh.complete);
}
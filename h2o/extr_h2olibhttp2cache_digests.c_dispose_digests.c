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
struct TYPE_4__ {int /*<<< orphan*/  url_and_etag; int /*<<< orphan*/  url_only; } ;
struct TYPE_5__ {TYPE_1__ fresh; } ;
typedef  TYPE_2__ h2o_cache_digests_t ;

/* Variables and functions */
 int /*<<< orphan*/  dispose_frame_vector (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dispose_digests(h2o_cache_digests_t *digests)
{
    dispose_frame_vector(&digests->fresh.url_only);
    dispose_frame_vector(&digests->fresh.url_and_etag);
}
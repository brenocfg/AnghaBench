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
struct uma_bucket_zone {scalar_t__ ubz_entries; int /*<<< orphan*/  ubz_zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  UMA_RECLAIM_DRAIN ; 
 struct uma_bucket_zone* bucket_zones ; 
 int /*<<< orphan*/  uma_zone_reclaim (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bucket_zone_drain(void)
{
	struct uma_bucket_zone *ubz;

	for (ubz = &bucket_zones[0]; ubz->ubz_entries != 0; ubz++)
		uma_zone_reclaim(ubz->ubz_zone, UMA_RECLAIM_DRAIN);
}
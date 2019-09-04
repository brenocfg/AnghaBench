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

/* Variables and functions */
 int /*<<< orphan*/  cache_all_uri_uncached_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_uri_dump_uncached ; 
 int /*<<< orphan*/  cgsl_order_top ; 

__attribute__((used)) static void cache_dump_uncached_uries (void) {
  cache_all_uri_uncached_foreach (cache_uri_dump_uncached, cgsl_order_top);
}
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
 int /*<<< orphan*/  cache_all_uri_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_uri_acounters_clear ; 
 int /*<<< orphan*/  cgsl_order_top ; 

void cache_clear_all_acounters (void) {
  cache_all_uri_foreach (cache_uri_acounters_clear, cgsl_order_top);
}
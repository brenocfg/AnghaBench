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
 int /*<<< orphan*/  stats_buff ; 
 int /*<<< orphan*/  stats_prepare_stats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void statsx_stats (void) {
  stats_prepare_stats (0);
  tl_store_stats (stats_buff, 0);
}
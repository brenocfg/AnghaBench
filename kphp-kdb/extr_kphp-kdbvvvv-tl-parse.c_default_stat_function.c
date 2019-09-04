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
 int /*<<< orphan*/  prepare_stats (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tl_store_stats (char*,int /*<<< orphan*/ ) ; 

void default_stat_function (void) {
  static char buf[(1 << 12)];
  prepare_stats (0, buf, (1 << 12) - 2);
  tl_store_stats (buf, 0);
}
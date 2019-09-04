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
 int /*<<< orphan*/  uv__signal_global_init ; 
 int /*<<< orphan*/  uv__signal_global_init_guard ; 
 int /*<<< orphan*/  uv_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void uv__signal_global_once_init(void) {
  uv_once(&uv__signal_global_init_guard, uv__signal_global_init);
}
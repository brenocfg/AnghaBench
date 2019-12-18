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
struct al_eth_lm_context {int /*<<< orphan*/  debug; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */

void
al_eth_lm_debug_mode_set(struct al_eth_lm_context *lm_context,
    boolean_t enable)
{

	lm_context->debug = enable;
}
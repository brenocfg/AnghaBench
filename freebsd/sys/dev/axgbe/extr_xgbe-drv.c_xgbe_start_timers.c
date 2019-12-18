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
struct xgbe_prv_data {int /*<<< orphan*/  service_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  xgbe_service_timer ; 

__attribute__((used)) static void xgbe_start_timers(struct xgbe_prv_data *pdata)
{
	callout_reset(&pdata->service_timer, hz, xgbe_service_timer, pdata);
}
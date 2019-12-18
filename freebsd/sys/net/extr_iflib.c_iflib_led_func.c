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
typedef  void* if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_LOCK (void*) ; 
 int /*<<< orphan*/  CTX_UNLOCK (void*) ; 
 int /*<<< orphan*/  IFDI_LED_FUNC (void*,int) ; 

__attribute__((used)) static void
iflib_led_func(void *arg, int onoff)
{
	if_ctx_t ctx = arg;

	CTX_LOCK(ctx);
	IFDI_LED_FUNC(ctx, onoff);
	CTX_UNLOCK(ctx);
}
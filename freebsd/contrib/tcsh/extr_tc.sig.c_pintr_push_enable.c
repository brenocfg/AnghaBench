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
 int /*<<< orphan*/  cleanup_push (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_pending_signals () ; 
 int pintr_disabled ; 
 int /*<<< orphan*/  pintr_disabled_restore ; 

void
pintr_push_enable(int *saved)
{
    *saved = pintr_disabled;
    pintr_disabled = 0;
    cleanup_push(saved, pintr_disabled_restore);
    handle_pending_signals();
}
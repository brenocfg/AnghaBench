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
 int /*<<< orphan*/  alrmcatch () ; 
 int /*<<< orphan*/  alrmcatch_disabled ; 
 scalar_t__ alrmcatch_pending ; 
 int /*<<< orphan*/  handle_interrupt ; 
 int /*<<< orphan*/  pchild () ; 
 int /*<<< orphan*/  pchild_disabled ; 
 scalar_t__ pchild_pending ; 
 int /*<<< orphan*/  phup () ; 
 int /*<<< orphan*/  phup_disabled ; 
 scalar_t__ phup_pending ; 
 int /*<<< orphan*/  pintr () ; 
 int /*<<< orphan*/  pintr_disabled ; 
 scalar_t__ pintr_pending ; 

int
handle_pending_signals(void)
{
    int rv = 0;
    if (!phup_disabled && phup_pending) {
	phup_pending = 0;
	handle_interrupt++;
	phup();
	handle_interrupt--;
    }
    if (!pintr_disabled && pintr_pending) {
	pintr_pending = 0;
	handle_interrupt++;
	pintr();
	handle_interrupt--;
	rv = 1;
    }
    if (!pchild_disabled && pchild_pending) {
	pchild_pending = 0;
	handle_interrupt++;
	pchild();
	handle_interrupt--;
    }
    if (!alrmcatch_disabled && alrmcatch_pending) {
	alrmcatch_pending = 0;
	handle_interrupt++;
	alrmcatch();
	handle_interrupt--;
    }
    return rv;
}
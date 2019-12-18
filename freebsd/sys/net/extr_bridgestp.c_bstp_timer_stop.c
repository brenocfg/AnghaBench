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
struct bstp_timer {scalar_t__ latched; scalar_t__ active; scalar_t__ value; } ;

/* Variables and functions */

__attribute__((used)) static void
bstp_timer_stop(struct bstp_timer *t)
{
	t->value = 0;
	t->active = 0;
	t->latched = 0;
}
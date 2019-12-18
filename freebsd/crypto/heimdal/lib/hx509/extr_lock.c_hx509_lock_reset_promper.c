#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hx509_lock ;
struct TYPE_3__ {int /*<<< orphan*/ * prompt_data; int /*<<< orphan*/ * prompt; } ;

/* Variables and functions */

void
hx509_lock_reset_promper(hx509_lock lock)
{
    lock->prompt = NULL;
    lock->prompt_data = NULL;
}
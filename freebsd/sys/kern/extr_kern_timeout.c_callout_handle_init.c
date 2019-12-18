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
struct callout_handle {int /*<<< orphan*/ * callout; } ;

/* Variables and functions */

void
callout_handle_init(struct callout_handle *handle)
{
	handle->callout = NULL;
}
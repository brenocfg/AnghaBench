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
struct push_cas_option {int /*<<< orphan*/  nr; int /*<<< orphan*/  use_tracking_for_rest; } ;

/* Variables and functions */

int is_empty_cas(const struct push_cas_option *cas)
{
	return !cas->use_tracking_for_rest && !cas->nr;
}
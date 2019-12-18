#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t len; } ;
struct oidname {scalar_t__* labels; TYPE_1__ oid; } ;

/* Variables and functions */

__attribute__((used)) static bool
oidname_has_labels(const struct oidname *on)
{
	size_t i;

	for (i = 0; i < on->oid.len; ++i)
		if (on->labels[i] != 0)
			return (true);
	return (false);
}
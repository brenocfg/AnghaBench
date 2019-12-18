#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sbp2_logical_unit {TYPE_2__* tgt; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* unit; } ;
struct TYPE_3__ {struct device const device; } ;

/* Variables and functions */

__attribute__((used)) static const struct device *lu_dev(const struct sbp2_logical_unit *lu)
{
	return &lu->tgt->unit->device;
}
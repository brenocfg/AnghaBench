#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  min_rights; int /*<<< orphan*/  max_rights; } ;
typedef  TYPE_1__ limited_rights_t ;

/* Variables and functions */

__attribute__((used)) static void
combine_right_limits(limited_rights_t *target,
                     const limited_rights_t *rights)
{
  target->max_rights |= rights->max_rights;
  target->min_rights &= rights->min_rights;
}
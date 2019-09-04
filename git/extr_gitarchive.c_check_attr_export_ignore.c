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
struct attr_check {TYPE_1__* items; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ ATTR_TRUE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_attr_export_ignore(const struct attr_check *check)
{
	return check && ATTR_TRUE(check->items[0].value);
}
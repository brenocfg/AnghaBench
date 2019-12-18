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
typedef  int /*<<< orphan*/  uint8_t ;
struct hast_resource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  control_set_role_common (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct hast_resource*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
control_set_role(struct hast_resource *res, uint8_t role)
{

	control_set_role_common(NULL, NULL, role, res, NULL, 0);
}
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
struct TYPE_3__ {int /*<<< orphan*/  metrics; } ;
typedef  int /*<<< orphan*/  GModule ;
typedef  TYPE_1__ GHolderItem ;
typedef  int /*<<< orphan*/  GDash ;

/* Variables and functions */
 int /*<<< orphan*/  set_dash_metrics (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_item_to_dash (GDash ** dash, GHolderItem item, GModule module)
{
  set_dash_metrics (dash, item.metrics, module, 0);
}
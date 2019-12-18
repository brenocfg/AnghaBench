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
struct TYPE_4__ {int /*<<< orphan*/  currentBar; } ;
typedef  TYPE_1__ Panel ;

/* Variables and functions */
 int /*<<< orphan*/  FunctionBar_draw (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Panel* setCurrentPanel(Panel* panel) {
   FunctionBar_draw(panel->currentBar, NULL);
   return panel;
}
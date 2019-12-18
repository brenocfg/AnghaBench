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
typedef  int /*<<< orphan*/  Htop_Action ;

/* Variables and functions */
 int /*<<< orphan*/  Platform_actionSetIOPriority ; 

void Platform_setBindings(Htop_Action* keys) {
   keys['i'] = Platform_actionSetIOPriority;
}
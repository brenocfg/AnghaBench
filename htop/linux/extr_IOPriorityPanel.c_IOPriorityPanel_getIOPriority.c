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
struct TYPE_2__ {int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  Panel ;
typedef  TYPE_1__ ListItem ;
typedef  int /*<<< orphan*/  IOPriority ;

/* Variables and functions */
 scalar_t__ Panel_getSelected (int /*<<< orphan*/ *) ; 

IOPriority IOPriorityPanel_getIOPriority(Panel* this) {
   return (IOPriority) ( ((ListItem*) Panel_getSelected(this))->key );
}
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
struct TYPE_4__ {int value; } ;
typedef  TYPE_1__ item_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_QLINK_INIT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlink ; 

__attribute__((used)) static void
item_init(item_t *item, int value) {
	item->value = value;
	ISC_QLINK_INIT(item, qlink);
}
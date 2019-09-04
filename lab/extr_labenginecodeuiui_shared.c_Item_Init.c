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
struct TYPE_4__ {float textscale; int /*<<< orphan*/  window; } ;
typedef  TYPE_1__ itemDef_t ;

/* Variables and functions */
 int /*<<< orphan*/  Window_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void Item_Init(itemDef_t *item) {
	if (item == NULL) {
		return;
	}

	memset(item, 0, sizeof(itemDef_t));
	item->textscale = 0.55f;
	Window_Init(&item->window);
}
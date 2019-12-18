#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {TYPE_1__* settings; } ;
struct TYPE_6__ {int key; } ;
struct TYPE_5__ {int changed; int* fields; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  ProcessField ;
typedef  int /*<<< orphan*/  Panel ;
typedef  TYPE_2__ ListItem ;
typedef  TYPE_3__ ColumnsPanel ;

/* Variables and functions */
 scalar_t__ Panel_get (int /*<<< orphan*/ *,int) ; 
 int Panel_size (int /*<<< orphan*/ *) ; 
 TYPE_4__* Process_fields ; 
 int* xRealloc (int*,int) ; 

void ColumnsPanel_update(Panel* super) {
   ColumnsPanel* this = (ColumnsPanel*) super;
   int size = Panel_size(super);
   this->settings->changed = true;
   this->settings->fields = xRealloc(this->settings->fields, sizeof(ProcessField) * (size+1));
   this->settings->flags = 0;
   for (int i = 0; i < size; i++) {
      int key = ((ListItem*) Panel_get(super, i))->key;
      this->settings->fields[i] = key;
      this->settings->flags |= Process_fields[key].flags;
   }
   this->settings->fields[size] = 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_7__ {TYPE_1__* modes; scalar_t__ filtering; } ;
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
struct TYPE_5__ {char* buffer; } ;
typedef  int /*<<< orphan*/  Panel ;
typedef  int /*<<< orphan*/  Object ;
typedef  TYPE_2__ ListItem ;
typedef  TYPE_3__ IncSet ;

/* Variables and functions */
 size_t INC_FILTER ; 
 int /*<<< orphan*/  Panel_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Panel_getSelected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Panel_prune (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Panel_setSelected (int /*<<< orphan*/ *,int) ; 
 scalar_t__ String_contains_i (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * Vector_get (int /*<<< orphan*/ *,int) ; 
 int Vector_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void updateWeakPanel(IncSet* this, Panel* panel, Vector* lines) {
   Object* selected = Panel_getSelected(panel);
   Panel_prune(panel);
   if (this->filtering) {
      int n = 0;
      const char* incFilter = this->modes[INC_FILTER].buffer;
      for (int i = 0; i < Vector_size(lines); i++) {
         ListItem* line = (ListItem*)Vector_get(lines, i);
         if (String_contains_i(line->value, incFilter)) {
            Panel_add(panel, (Object*)line);
            if (selected == (Object*)line) Panel_setSelected(panel, n);
            n++;
         }
      }
   } else {
      for (int i = 0; i < Vector_size(lines); i++) {
         Object* line = Vector_get(lines, i);
         Panel_add(panel, line);
         if (selected == line) Panel_setSelected(panel, i);
      }
   }
}
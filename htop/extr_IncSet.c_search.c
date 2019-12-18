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
struct TYPE_3__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  bar; } ;
typedef  int /*<<< orphan*/  Panel ;
typedef  int /*<<< orphan*/  (* IncMode_GetPanelValue ) (int /*<<< orphan*/ *,int) ;
typedef  TYPE_1__ IncMode ;

/* Variables and functions */
 int /*<<< orphan*/ * CRT_colors ; 
 size_t FAILED_SEARCH ; 
 int /*<<< orphan*/  FunctionBar_draw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionBar_drawAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Panel_setSelected (int /*<<< orphan*/ *,int) ; 
 int Panel_size (int /*<<< orphan*/ *) ; 
 scalar_t__ String_contains_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool search(IncMode* mode, Panel* panel, IncMode_GetPanelValue getPanelValue) {
   int size = Panel_size(panel);
   bool found = false;
   for (int i = 0; i < size; i++) {
      if (String_contains_i(getPanelValue(panel, i), mode->buffer)) {
         Panel_setSelected(panel, i);
         found = true;
         break;
      }
   }
   if (found)
      FunctionBar_draw(mode->bar, mode->buffer);
   else
      FunctionBar_drawAttr(mode->bar, mode->buffer, CRT_colors[FAILED_SEARCH]);
   return found;
}
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
struct TYPE_3__ {int /*<<< orphan*/  scr; int /*<<< orphan*/  settings; } ;
typedef  int /*<<< orphan*/  Panel ;
typedef  TYPE_1__ CategoriesPanel ;

/* Variables and functions */
 scalar_t__ AvailableColumnsPanel_new (int /*<<< orphan*/ *) ; 
 scalar_t__ ColumnsPanel_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScreenManager_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void CategoriesPanel_makeColumnsPage(CategoriesPanel* this) {
   Panel* columns = (Panel*) ColumnsPanel_new(this->settings);
   Panel* availableColumns = (Panel*) AvailableColumnsPanel_new(columns);
   ScreenManager_add(this->scr, columns, 20);
   ScreenManager_add(this->scr, availableColumns, -1);
}
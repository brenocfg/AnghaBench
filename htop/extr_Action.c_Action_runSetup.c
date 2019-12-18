#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  height; } ;
struct TYPE_10__ {scalar_t__ changed; } ;
typedef  TYPE_1__ Settings ;
typedef  int /*<<< orphan*/  ScreenManager ;
typedef  int /*<<< orphan*/  ProcessList ;
typedef  int /*<<< orphan*/  Panel ;
typedef  TYPE_2__ Header ;
typedef  int /*<<< orphan*/  CategoriesPanel ;

/* Variables and functions */
 int /*<<< orphan*/  CategoriesPanel_makeMetersPage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CategoriesPanel_new (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HORIZONTAL ; 
 int /*<<< orphan*/  Header_writeBackToSettings (TYPE_2__ const*) ; 
 int /*<<< orphan*/  ScreenManager_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ScreenManager_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ScreenManager_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_2__ const*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ScreenManager_run (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 

__attribute__((used)) static void Action_runSetup(Settings* settings, const Header* header, ProcessList* pl) {
   ScreenManager* scr = ScreenManager_new(0, header->height, 0, -1, HORIZONTAL, header, settings, true);
   CategoriesPanel* panelCategories = CategoriesPanel_new(scr, settings, (Header*) header, pl);
   ScreenManager_add(scr, (Panel*) panelCategories, 16);
   CategoriesPanel_makeMetersPage(panelCategories);
   Panel* panelFocus;
   int ch;
   ScreenManager_run(scr, &panelFocus, &ch);
   ScreenManager_delete(scr);
   if (settings->changed) {
      Header_writeBackToSettings(header);
   }
}
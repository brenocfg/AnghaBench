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
struct TYPE_4__ {int x1; int y1; int x2; int y2; int owner; int allowFocusChange; int /*<<< orphan*/  const* settings; int /*<<< orphan*/  const* header; scalar_t__ panelCount; int /*<<< orphan*/  panels; int /*<<< orphan*/  orientation; } ;
typedef  int /*<<< orphan*/  Settings ;
typedef  TYPE_1__ ScreenManager ;
typedef  int /*<<< orphan*/  Orientation ;
typedef  int /*<<< orphan*/  Header ;

/* Variables and functions */
 int /*<<< orphan*/  Class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFAULT_SIZE ; 
 int /*<<< orphan*/  Panel ; 
 int /*<<< orphan*/  Vector_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* xMalloc (int) ; 

ScreenManager* ScreenManager_new(int x1, int y1, int x2, int y2, Orientation orientation, const Header* header, const Settings* settings, bool owner) {
   ScreenManager* this;
   this = xMalloc(sizeof(ScreenManager));
   this->x1 = x1;
   this->y1 = y1;
   this->x2 = x2;
   this->y2 = y2;
   this->orientation = orientation;
   this->panels = Vector_new(Class(Panel), owner, DEFAULT_SIZE);
   this->panelCount = 0;
   this->header = header;
   this->settings = settings;
   this->owner = owner;
   this->allowFocusChange = true;
   return this;
}
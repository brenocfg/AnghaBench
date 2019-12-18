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
struct TYPE_3__ {int /*<<< orphan*/  display; int /*<<< orphan*/  inc; int /*<<< orphan*/  lines; } ;
typedef  int /*<<< orphan*/  Object ;
typedef  int /*<<< orphan*/  ListItem ;
typedef  TYPE_1__ InfoScreen ;

/* Variables and functions */
 char* IncSet_filter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ListItem_append (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  Panel_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Panel_get (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ Panel_size (int /*<<< orphan*/ ) ; 
 scalar_t__ String_contains_i (char const*,char const*) ; 
 scalar_t__ Vector_get (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ Vector_size (int /*<<< orphan*/ ) ; 

void InfoScreen_appendLine(InfoScreen* this, const char* line) {
   ListItem* last = (ListItem*)Vector_get(this->lines, Vector_size(this->lines)-1);
   ListItem_append(last, line);
   const char* incFilter = IncSet_filter(this->inc);
   if (incFilter && Panel_get(this->display, Panel_size(this->display)-1) != (Object*)last && String_contains_i(line, incFilter))
      Panel_add(this->display, (Object*)last);
}
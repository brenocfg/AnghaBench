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
struct TYPE_3__ {int /*<<< orphan*/  lines; int /*<<< orphan*/  display; int /*<<< orphan*/  inc; } ;
typedef  int /*<<< orphan*/  Object ;
typedef  TYPE_1__ InfoScreen ;

/* Variables and functions */
 char* IncSet_filter (int /*<<< orphan*/ ) ; 
 scalar_t__ ListItem_new (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Panel_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ String_contains_i (char const*,char const*) ; 
 int /*<<< orphan*/  Vector_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ Vector_get (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ Vector_size (int /*<<< orphan*/ ) ; 

void InfoScreen_addLine(InfoScreen* this, const char* line) {
   Vector_add(this->lines, (Object*) ListItem_new(line, 0));
   const char* incFilter = IncSet_filter(this->inc);
   if (!incFilter || String_contains_i(line, incFilter))
      Panel_add(this->display, (Object*)Vector_get(this->lines, Vector_size(this->lines)-1));
}
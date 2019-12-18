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
struct TYPE_3__ {char* text; } ;
typedef  int /*<<< orphan*/  RichString ;
typedef  int /*<<< orphan*/  Object ;
typedef  TYPE_1__ CheckItem ;

/* Variables and functions */
 size_t CHECK_BOX ; 
 size_t CHECK_MARK ; 
 size_t CHECK_TEXT ; 
 int /*<<< orphan*/ * CRT_colors ; 
 scalar_t__ CheckItem_get (TYPE_1__*) ; 
 int /*<<< orphan*/  RichString_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RichString_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CheckItem_display(Object* cast, RichString* out) {
   CheckItem* this = (CheckItem*)cast;
   assert (this != NULL);
   RichString_write(out, CRT_colors[CHECK_BOX], "[");
   if (CheckItem_get(this))
      RichString_append(out, CRT_colors[CHECK_MARK], "x");
   else
      RichString_append(out, CRT_colors[CHECK_MARK], " ");
   RichString_append(out, CRT_colors[CHECK_BOX], "] ");
   RichString_append(out, CRT_colors[CHECK_TEXT], this->text);
}
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
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
typedef  TYPE_1__ itemDef_t ;

/* Variables and functions */
 int /*<<< orphan*/  Menu_ShowItemByName (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ String_Parse (char**,char const**) ; 
 int /*<<< orphan*/  qfalse ; 

void Script_Hide(itemDef_t *item, char **args) {
  const char *name;
  if (String_Parse(args, &name)) {
    Menu_ShowItemByName(item->parent, name, qfalse);
  }
}
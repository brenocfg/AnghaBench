#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  itemDef_t ;

/* Variables and functions */
 int /*<<< orphan*/  Menus_OpenByName (char const*) ; 
 scalar_t__ String_Parse (char**,char const**) ; 

void Script_Open(itemDef_t *item, char **args) {
  const char *name;
  if (String_Parse(args, &name)) {
    Menus_OpenByName(name);
  }
}
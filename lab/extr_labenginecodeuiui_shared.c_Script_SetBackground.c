#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  background; } ;
struct TYPE_6__ {TYPE_1__ window; } ;
typedef  TYPE_2__ itemDef_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* registerShaderNoMip ) (char const*) ;} ;

/* Variables and functions */
 TYPE_4__* DC ; 
 scalar_t__ String_Parse (char**,char const**) ; 
 int /*<<< orphan*/  stub1 (char const*) ; 

void Script_SetBackground(itemDef_t *item, char **args) {
  const char *name;
  // expecting name to set asset to
  if (String_Parse(args, &name)) {
    item->window.background = DC->registerShaderNoMip(name);
  }
}
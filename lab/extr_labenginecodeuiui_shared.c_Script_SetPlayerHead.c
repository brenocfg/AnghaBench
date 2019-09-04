#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  itemDef_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* setCVar ) (char*,char const*) ;} ;

/* Variables and functions */
 TYPE_1__* DC ; 
 scalar_t__ String_Parse (char**,char const**) ; 
 int /*<<< orphan*/  stub1 (char*,char const*) ; 

void Script_SetPlayerHead(itemDef_t *item, char **args) {
  const char *name;
  if (String_Parse(args, &name)) {
    DC->setCVar("team_headmodel", name);
  }
}
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
struct TYPE_2__ {float (* getCVarValue ) (char const*) ;} ;

/* Variables and functions */
 TYPE_1__* DC ; 
 int /*<<< orphan*/  Menus_OpenByName (char const*) ; 
 scalar_t__ String_Parse (char**,char const**) ; 
 float stub1 (char const*) ; 

void Script_ConditionalOpen(itemDef_t *item, char **args) {
	const char *cvar;
	const char *name1;
	const char *name2;
	float           val;

	if ( String_Parse(args, &cvar) && String_Parse(args, &name1) && String_Parse(args, &name2) ) {
		val = DC->getCVarValue( cvar );
		if ( val == 0.f ) {
			Menus_OpenByName(name2);
		} else {
			Menus_OpenByName(name1);
		}
	}
}
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
typedef  int /*<<< orphan*/  name ;
struct TYPE_3__ {int /*<<< orphan*/  classname; } ;
typedef  TYPE_1__ gitem_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int trap_Cvar_VariableIntegerValue (char*) ; 

int G_ItemDisabled( gitem_t *item ) {

	char name[128];

	Com_sprintf(name, sizeof(name), "disable_%s", item->classname);
	return trap_Cvar_VariableIntegerValue( name );
}
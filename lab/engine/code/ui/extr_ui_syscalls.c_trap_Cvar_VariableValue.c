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
struct TYPE_2__ {float f; int /*<<< orphan*/  i; } ;
typedef  TYPE_1__ floatint_t ;

/* Variables and functions */
 int /*<<< orphan*/  UI_CVAR_VARIABLEVALUE ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,char const*) ; 

float trap_Cvar_VariableValue( const char *var_name ) {
	floatint_t fi;
	fi.i = syscall( UI_CVAR_VARIABLEVALUE, var_name );
	return fi.f;
}
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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_3__ {float min; float max; int /*<<< orphan*/  string; int /*<<< orphan*/  name; int /*<<< orphan*/  integral; int /*<<< orphan*/  validate; } ;
typedef  TYPE_1__ cvar_t ;

/* Variables and functions */
 int /*<<< orphan*/  Cvar_Set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtrue ; 

void Cvar_CheckRange( cvar_t *var, float min, float max, qboolean integral )
{
	var->validate = qtrue;
	var->min = min;
	var->max = max;
	var->integral = integral;

	// Force an initial range check
	Cvar_Set( var->name, var->string );
}
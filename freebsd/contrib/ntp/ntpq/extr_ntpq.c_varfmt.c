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
typedef  int /*<<< orphan*/  u_short ;
typedef  size_t u_int ;
struct TYPE_3__ {int /*<<< orphan*/  fmt; int /*<<< orphan*/  varname; } ;

/* Variables and functions */
 size_t COUNTOF (TYPE_1__*) ; 
 int /*<<< orphan*/  PADDING ; 
 TYPE_1__* cookedvars ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

u_short
varfmt(const char * varname)
{
	u_int n;

	for (n = 0; n < COUNTOF(cookedvars); n++)
		if (!strcmp(varname, cookedvars[n].varname))
			return cookedvars[n].fmt;

	return PADDING;
}
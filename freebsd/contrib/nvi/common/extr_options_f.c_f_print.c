#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
struct TYPE_8__ {int /*<<< orphan*/ * opts; } ;
typedef  TYPE_1__ SCR ;
typedef  int /*<<< orphan*/  OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  F_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_STRDUP ; 
 int /*<<< orphan*/  O_CLR (TYPE_1__*,int) ; 
 int O_OCTAL ; 
 int /*<<< orphan*/  O_SET (TYPE_1__*,int) ; 
 int /*<<< orphan*/  SC_SCR_REFORMAT ; 
 scalar_t__ o_set (TYPE_1__*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v_key_ilookup (TYPE_1__*) ; 

int
f_print(
	SCR *sp,
	OPTION *op,
	char *str,
	u_long *valp)
{
	int offset = op - sp->opts;

	/* Preset the value, needed for reinitialization of lookup table. */
	if (offset == O_OCTAL) {
		if (*valp)
			O_SET(sp, offset);
		else
			O_CLR(sp, offset);
	} else if (o_set(sp, offset, OS_STRDUP, str, 0))
		return(1);

	/* Reinitialize the key fast lookup table. */
	v_key_ilookup(sp);

	/* Reformat the screen. */
	F_SET(sp, SC_SCR_REFORMAT);
	return (0);
}
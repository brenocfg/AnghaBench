#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {long t_minrows; long t_rows; int rows; } ;
typedef  TYPE_1__ SCR ;

/* Variables and functions */
 int /*<<< orphan*/  F_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int HMAP ; 
 int /*<<< orphan*/  SC_SCR_REDRAW ; 
 int TMAP ; 

int
vs_crel(SCR *sp, long int count)
{
	sp->t_minrows = sp->t_rows = count;
	if (sp->t_rows > sp->rows - 1)
		sp->t_minrows = sp->t_rows = sp->rows - 1;
	TMAP = HMAP + (sp->t_rows - 1);
	F_SET(sp, SC_SCR_REDRAW);
	return (0);
}
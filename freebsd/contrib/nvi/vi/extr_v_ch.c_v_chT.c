#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cno; } ;
struct TYPE_7__ {TYPE_1__ m_stop; TYPE_1__ m_final; } ;
typedef  TYPE_2__ VICMD ;
struct TYPE_8__ {int /*<<< orphan*/  csearchdir; } ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 int /*<<< orphan*/  TSEARCH ; 
 TYPE_5__* VIP (int /*<<< orphan*/ *) ; 
 scalar_t__ v_chF (int /*<<< orphan*/ *,TYPE_2__*) ; 

int
v_chT(SCR *sp, VICMD *vp)
{
	if (v_chF(sp, vp))
		return (1);

	/*
	 * v_chF places the cursor on the character, where the 'T'
	 * command wants it to its right.  We know this is safe since
	 * we had to move left for v_chF() to have succeeded.
	 */
	++vp->m_stop.cno;
	vp->m_final = vp->m_stop;

	VIP(sp)->csearchdir = TSEARCH;
	return (0);
}
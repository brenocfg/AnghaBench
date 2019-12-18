#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  cno; } ;
struct TYPE_8__ {TYPE_1__ m_stop; TYPE_1__ m_final; } ;
typedef  TYPE_2__ VICMD ;
struct TYPE_9__ {int /*<<< orphan*/  csearchdir; } ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 int /*<<< orphan*/  ISMOTION (TYPE_2__*) ; 
 TYPE_5__* VIP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tSEARCH ; 
 scalar_t__ v_chf (int /*<<< orphan*/ *,TYPE_2__*) ; 

int
v_cht(SCR *sp, VICMD *vp)
{
	if (v_chf(sp, vp))
		return (1);

	/*
	 * v_chf places the cursor on the character, where the 't'
	 * command wants it to its left.  We know this is safe since
	 * we had to move right for v_chf() to have succeeded.
	 */
	--vp->m_stop.cno;

	/*
	 * Make any necessary correction to the motion decision made
	 * by the v_chf routine.
	 */
	if (!ISMOTION(vp))
		vp->m_final = vp->m_stop;

	VIP(sp)->csearchdir = tSEARCH;
	return (0);
}
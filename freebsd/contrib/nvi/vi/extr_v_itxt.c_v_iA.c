#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  lno; } ;
struct TYPE_10__ {TYPE_1__ m_start; } ;
typedef  TYPE_2__ VICMD ;
struct TYPE_11__ {size_t cno; } ;
typedef  TYPE_3__ SCR ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_CORRECT ; 
 int /*<<< orphan*/  db_get (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 int v_ia (TYPE_3__*,TYPE_2__*) ; 

int
v_iA(SCR *sp, VICMD *vp)
{
	size_t len;

	if (!db_get(sp, vp->m_start.lno, 0, NULL, &len))
		sp->cno = len == 0 ? 0 : len - 1;

	LOG_CORRECT;

	return (v_ia(sp, vp));
}
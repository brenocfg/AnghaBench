#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  recno_t ;
struct TYPE_5__ {scalar_t__ rcm; } ;
typedef  TYPE_1__ SCR ;

/* Variables and functions */
 scalar_t__ db_get (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 size_t vs_colpos (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

size_t
vs_rcm(SCR *sp, recno_t lno, int islast)
{
	size_t len;

	/* Last character is easy, and common. */
	if (islast) {
		if (db_get(sp, lno, 0, NULL, &len) || len == 0)
			return (0);
		return (len - 1);
	}

	/* First character is easy, and common. */
	if (sp->rcm == 0)
		return (0);

	return (vs_colpos(sp, lno, sp->rcm));
}
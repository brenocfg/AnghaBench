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
struct TYPE_3__ {scalar_t__ e_flno; scalar_t__ e_tlno; } ;
typedef  int /*<<< orphan*/  SMAP ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ EVENT ;

/* Variables and functions */
 int /*<<< orphan*/ * HMAP ; 
 int /*<<< orphan*/  SMAP_FLUSH (int /*<<< orphan*/ *) ; 
 scalar_t__ vs_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
vs_repaint(
	SCR *sp,
	EVENT *evp)
{
	SMAP *smp;

	for (; evp->e_flno <= evp->e_tlno; ++evp->e_flno) {
		smp = HMAP + evp->e_flno - 1;
		SMAP_FLUSH(smp);
		if (vs_line(sp, smp, NULL, NULL))
			return (1);
	}
	return (0);
}
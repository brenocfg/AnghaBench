#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gmonparam {int /*<<< orphan*/  state; int /*<<< orphan*/  lowpc; int /*<<< orphan*/  kcountsize; scalar_t__ kcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMON_PROF_OFF ; 
 int /*<<< orphan*/  GMON_PROF_ON ; 
 struct gmonparam _gmonparam ; 
 int /*<<< orphan*/  profil (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_scale ; 

void
moncontrol(int mode)
{
	struct gmonparam *p = &_gmonparam;

	if (mode) {
		/* start */
		profil((char *)p->kcount, p->kcountsize, p->lowpc, s_scale);
		p->state = GMON_PROF_ON;
	} else {
		/* stop */
		profil((char *)0, 0, 0, 0);
		p->state = GMON_PROF_OFF;
	}
}
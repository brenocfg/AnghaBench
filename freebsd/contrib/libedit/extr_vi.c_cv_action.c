#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int wint_t ;
typedef  int /*<<< orphan*/  el_action_t ;
struct TYPE_11__ {int action; scalar_t__ pos; } ;
struct TYPE_12__ {TYPE_3__ c_vcmd; } ;
struct TYPE_10__ {scalar_t__ cursor; scalar_t__ buffer; scalar_t__ lastchar; } ;
struct TYPE_9__ {int /*<<< orphan*/  key; int /*<<< orphan*/  current; } ;
struct TYPE_13__ {TYPE_4__ el_chared; TYPE_2__ el_line; TYPE_1__ el_map; } ;
typedef  TYPE_5__ EditLine ;

/* Variables and functions */
 int /*<<< orphan*/  CC_ARGHACK ; 
 int /*<<< orphan*/  CC_ERROR ; 
 int /*<<< orphan*/  CC_REFRESH ; 
 int INSERT ; 
 int NOP ; 
 int YANK ; 
 int /*<<< orphan*/  cv_undo (TYPE_5__*) ; 
 int /*<<< orphan*/  cv_yank (TYPE_5__*,scalar_t__,int) ; 

__attribute__((used)) static el_action_t
cv_action(EditLine *el, wint_t c)
{

	if (el->el_chared.c_vcmd.action != NOP) {
		/* 'cc', 'dd' and (possibly) friends */
		if (c != (wint_t)el->el_chared.c_vcmd.action)
			return CC_ERROR;

		if (!(c & YANK))
			cv_undo(el);
		cv_yank(el, el->el_line.buffer,
		    (int)(el->el_line.lastchar - el->el_line.buffer));
		el->el_chared.c_vcmd.action = NOP;
		el->el_chared.c_vcmd.pos = 0;
		if (!(c & YANK)) {
			el->el_line.lastchar = el->el_line.buffer;
			el->el_line.cursor = el->el_line.buffer;
		}
		if (c & INSERT)
			el->el_map.current = el->el_map.key;

		return CC_REFRESH;
	}
	el->el_chared.c_vcmd.pos = el->el_line.cursor;
	el->el_chared.c_vcmd.action = c;
	return CC_ARGHACK;
}
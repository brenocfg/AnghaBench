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
typedef  scalar_t__ wchar_t ;
struct TYPE_3__ {scalar_t__ wc; int /*<<< orphan*/ * ref; } ;
typedef  TYPE_1__ collchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTERR ; 
 int /*<<< orphan*/  add_subst_pri (int /*<<< orphan*/ ) ; 
 size_t curr_weight ; 
 TYPE_1__* get_collchar (scalar_t__,int) ; 

void
add_subst_char(wchar_t wc)
{
	collchar_t *cc;


	if (((cc = get_collchar(wc, 1)) == NULL) ||
	    (cc->wc != wc)) {
		INTERR;
		return;
	}
	/* we take the weight for the character at that position */
	add_subst_pri(cc->ref[curr_weight]);
}
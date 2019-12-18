#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* lc_cap; struct TYPE_6__* lc_class; struct TYPE_6__* lc_style; } ;
typedef  TYPE_1__ login_cap_t ;

/* Variables and functions */
 int /*<<< orphan*/  cgetclose () ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* internal_array ; 
 scalar_t__ internal_arraysz ; 
 TYPE_1__* internal_string ; 
 scalar_t__ internal_stringsz ; 
 scalar_t__ lc_object_count ; 

void
login_close(login_cap_t * lc)
{
    if (lc) {
	free(lc->lc_style);
	free(lc->lc_class);
	free(lc->lc_cap);
	free(lc);
	if (--lc_object_count == 0) {
	    free(internal_string);
	    free(internal_array);
	    internal_array = NULL;
	    internal_arraysz = 0;
	    internal_string = NULL;
	    internal_stringsz = 0;
	    cgetclose();
	}
    }
}
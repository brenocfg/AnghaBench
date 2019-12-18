#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum protection_level { ____Placeholder_protection_level } protection_level ;
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  (* end ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * app_data ; 
 int data_prot ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_1__* mech ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sec_complete ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void
sec_end(void)
{
    if (mech != NULL) {
	if(mech->end)
	    (*mech->end)(app_data);
	if (app_data != NULL) {
	    memset(app_data, 0, mech->size);
	    free(app_data);
	    app_data = NULL;
	}
    }
    sec_complete = 0;
    data_prot = (enum protection_level)0;
}
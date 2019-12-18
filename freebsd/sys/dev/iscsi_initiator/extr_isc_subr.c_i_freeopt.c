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
struct TYPE_3__ {int /*<<< orphan*/ * initiatorName; int /*<<< orphan*/ * targetName; int /*<<< orphan*/ * targetAddress; } ;
typedef  TYPE_1__ isc_opt_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_ISC ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
i_freeopt(isc_opt_t *opt)
{
     debug_called(8);

     if(opt->targetAddress != NULL) {
	  free(opt->targetAddress, M_ISC);
	  opt->targetAddress = NULL;
     }
     if(opt->targetName != NULL) {
	  free(opt->targetName, M_ISC);
	  opt->targetName = NULL;
     }
     if(opt->initiatorName != NULL) {
	  free(opt->initiatorName, M_ISC);
	  opt->initiatorName = NULL;
     }
}
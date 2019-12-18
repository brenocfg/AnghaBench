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
typedef  union ctl_io {int dummy; } ctl_io ;
struct ctl_scsiio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_set_success (struct ctl_scsiio*) ; 

int
ctl_tur(struct ctl_scsiio *ctsio)
{

	CTL_DEBUG_PRINT(("ctl_tur\n"));

	ctl_set_success(ctsio);
	ctl_done((union ctl_io *)ctsio);

	return (CTL_RETVAL_COMPLETE);
}
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
typedef  scalar_t__ uint16_t ;
struct TYPE_10__ {int isp_nchan; } ;
typedef  TYPE_2__ ispsoftc_t ;
struct TYPE_11__ {scalar_t__ role; TYPE_1__* portdb; } ;
typedef  TYPE_3__ fcparam ;
struct TYPE_9__ {scalar_t__ state; scalar_t__ handle; } ;

/* Variables and functions */
 TYPE_3__* FCPARAM (TYPE_2__*,int) ; 
 scalar_t__ FC_PORTDB_STATE_NIL ; 
 scalar_t__ ISP_CAP_2KLOGIN (TYPE_2__*) ; 
 int /*<<< orphan*/  ISP_LOGERR ; 
 scalar_t__ ISP_ROLE_NONE ; 
 int MAX_FC_TARG ; 
 scalar_t__ NIL_HANDLE ; 
 scalar_t__ NPH_MAX ; 
 scalar_t__ NPH_RESERVED ; 
 scalar_t__ SNS_ID ; 
 int /*<<< orphan*/  isp_prt (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static uint16_t
isp_next_handle(ispsoftc_t *isp, uint16_t *ohp)
{
	fcparam *fcp;
	int i, chan, wrap;
	uint16_t handle, minh, maxh;

	handle = *ohp;
	if (ISP_CAP_2KLOGIN(isp)) {
		minh = 0;
		maxh = NPH_RESERVED - 1;
	} else {
		minh = SNS_ID + 1;
		maxh = NPH_MAX - 1;
	}
	wrap = 0;

next:
	if (handle == NIL_HANDLE) {
		handle = minh;
	} else {
		handle++;
		if (handle > maxh) {
			if (++wrap >= 2) {
				isp_prt(isp, ISP_LOGERR, "Out of port handles!");
				return (NIL_HANDLE);
			}
			handle = minh;
		}
	}
	for (chan = 0; chan < isp->isp_nchan; chan++) {
		fcp = FCPARAM(isp, chan);
		if (fcp->role == ISP_ROLE_NONE)
			continue;
		for (i = 0; i < MAX_FC_TARG; i++) {
			if (fcp->portdb[i].state != FC_PORTDB_STATE_NIL &&
			    fcp->portdb[i].handle == handle)
				goto next;
		}
	}
	*ohp = handle;
	return (handle);
}
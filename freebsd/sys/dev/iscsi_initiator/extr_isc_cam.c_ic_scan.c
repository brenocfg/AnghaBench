#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* spriv_ptr0; int /*<<< orphan*/  cbfcnp; int /*<<< orphan*/  path; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct TYPE_6__ {scalar_t__ sid; int flags; scalar_t__ target_nluns; int /*<<< orphan*/  cam_path; } ;
typedef  TYPE_2__ isc_session_t ;

/* Variables and functions */
 int ENODEV ; 
 int ISC_CAMDEVS ; 
 int ISC_SCANWAIT ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int hz ; 
 int /*<<< orphan*/  scan_callback ; 
 int /*<<< orphan*/  sdebug (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  tsleep (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 
 union ccb* xpt_alloc_ccb () ; 
 int /*<<< orphan*/  xpt_rescan (union ccb*) ; 

__attribute__((used)) static int
ic_scan(isc_session_t *sp)
{
     union ccb	*ccb;

     debug_called(8);
     sdebug(2, "scanning sid=%d", sp->sid);

     sp->flags &= ~ISC_CAMDEVS;
     sp->flags |= ISC_SCANWAIT;

     ccb = xpt_alloc_ccb();
     ccb->ccb_h.path		= sp->cam_path;
     ccb->ccb_h.cbfcnp		= scan_callback;
     ccb->ccb_h.spriv_ptr0	= sp;

     xpt_rescan(ccb);

     while(sp->flags & ISC_SCANWAIT)
	  tsleep(sp, PRIBIO, "ffp", 5*hz); // the timeout time should
					    // be configurable
     sdebug(2, "# of luns=%d", sp->target_nluns);

     if(sp->target_nluns > 0) {
	  sp->flags |= ISC_CAMDEVS;
	  return 0;
     }

     return ENODEV;
}
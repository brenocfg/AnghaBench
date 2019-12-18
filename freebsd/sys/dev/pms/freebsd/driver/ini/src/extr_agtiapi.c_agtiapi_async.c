#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_3__ {size_t target_id; } ;
struct ccb_getdev {TYPE_1__ ccb_h; } ;
struct cam_path {int dummy; } ;
struct agtiapi_softc {TYPE_2__* pDevList; } ;
struct TYPE_4__ {int /*<<< orphan*/  qdepth; } ;
typedef  TYPE_2__ ag_device_t ;
typedef  size_t U32 ;

/* Variables and functions */
#define  AC_FOUND_DEVICE 128 
 size_t INDEX (struct agtiapi_softc*,size_t) ; 
 int /*<<< orphan*/  agtiapi_adjust_queue_depth (struct cam_path*,int /*<<< orphan*/ ) ; 
 size_t maxTargets ; 

__attribute__((used)) static void
agtiapi_async(void *callback_arg, u_int32_t code,
	       struct cam_path *path, void *arg)
{
	struct agtiapi_softc *pmsc;
	U32        TID;
	ag_device_t *targ;	
	pmsc = (struct agtiapi_softc*)callback_arg;
	switch (code) {
	case AC_FOUND_DEVICE:
	{
	    struct ccb_getdev *cgd;
	    cgd = (struct ccb_getdev *)arg;
	    if (cgd == NULL) {
		break;
	    }
	    TID = cgd->ccb_h.target_id;
	    if (TID >= 0 && TID < maxTargets){
                if (pmsc != NULL){
                    TID = INDEX(pmsc, TID);
                    targ   = &pmsc->pDevList[TID];
	            agtiapi_adjust_queue_depth(path, targ->qdepth);
                }
	    }
	    break;
        }
	default:
		break;
	}
}
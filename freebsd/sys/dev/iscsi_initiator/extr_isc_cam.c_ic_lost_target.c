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
struct TYPE_3__ {int /*<<< orphan*/ * cam_path; int /*<<< orphan*/  cam_mtx; } ;
typedef  TYPE_1__ isc_session_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_LOST_DEVICE ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdebug (int,char*,int) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ *) ; 

void
ic_lost_target(isc_session_t *sp, int target)
{
     debug_called(8);
     sdebug(2, "lost target=%d", target);

     if(sp->cam_path != NULL) {
	  mtx_lock(&sp->cam_mtx);
	  xpt_async(AC_LOST_DEVICE, sp->cam_path, NULL);
	  xpt_free_path(sp->cam_path);
	  mtx_unlock(&sp->cam_mtx);
	  sp->cam_path = 0; // XXX
     }
}
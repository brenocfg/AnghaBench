#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct cdev {TYPE_1__* si_drv2; } ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ isc_session_t ;

/* Variables and functions */
 int ISC_FFPHASE ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  debug (int,char*,...) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 scalar_t__ dev2unit (struct cdev*) ; 
 int hz ; 
 int /*<<< orphan*/  ism_stop (TYPE_1__*) ; 
 scalar_t__ max_sessions ; 
 int /*<<< orphan*/  sdebug (int,char*,int) ; 
 int /*<<< orphan*/  tsleep (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
iscsi_close(struct cdev *dev, int flag, int otyp, struct thread *td)
{
     isc_session_t	*sp;

     debug_called(8);

     debug(3, "session=%d flag=%x", dev2unit(dev), flag);

     if(dev2unit(dev) == max_sessions) {
	  return 0;
     }
     sp = dev->si_drv2;
     if(sp != NULL) {
	  sdebug(3, "sp->flags=%x", sp->flags );
	  /*
	   | if still in full phase, this probably means
	   | that something went really bad.
	   | it could be a result from 'shutdown', in which case
	   | we will ignore it (so buffers can be flushed).
	   | the problem is that there is no way of differentiating
	   | between a shutdown procedure and 'iscontrol' dying.
	   */
	  if(sp->flags & ISC_FFPHASE)
	       // delay in case this is a shutdown.
	       tsleep(sp, PRIBIO, "isc-cls", 60*hz);
	  ism_stop(sp);
     }
     debug(2, "done");
     return 0;
}
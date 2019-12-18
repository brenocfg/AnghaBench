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
struct cdev {TYPE_1__* si_drv2; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ isc_session_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_FFPHASE ; 
 int ic_init (TYPE_1__*) ; 
 int /*<<< orphan*/  ism_restart (TYPE_1__*) ; 
 int /*<<< orphan*/  sdebug (int,char*,int) ; 

__attribute__((used)) static int
i_fullfeature(struct cdev *dev, int flag)
{
     isc_session_t	*sp = dev->si_drv2;
     int		error;

     sdebug(2, "flag=%d", flag);

     error = 0;
     switch(flag) {
     case 0: // stop
         sp->flags &= ~ISC_FFPHASE;
         break;
     case 1: // start
         sp->flags |= ISC_FFPHASE;
         error = ic_init(sp);
         break;
     case 2: // restart
         sp->flags |= ISC_FFPHASE;
         ism_restart(sp);
         break;
     }
     return error;
}
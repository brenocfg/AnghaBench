#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct TYPE_6__ {struct thread* td; TYPE_5__* fp; int /*<<< orphan*/ * soc; } ;
typedef  TYPE_1__ isc_session_t ;
typedef  int /*<<< orphan*/  cap_rights_t ;
struct TYPE_7__ {int /*<<< orphan*/ * f_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SOCK_CLIENT ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int getsock_cap (struct thread*,int,int /*<<< orphan*/ ,TYPE_5__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_start_receiver (TYPE_1__*) ; 
 int /*<<< orphan*/  isc_stop_receiver (TYPE_1__*) ; 

__attribute__((used)) static int
i_setsoc(isc_session_t *sp, int fd, struct thread *td)
{
     cap_rights_t rights;
     int error = 0;

     if(sp->soc != NULL)
	  isc_stop_receiver(sp);

     error = getsock_cap(td, fd, cap_rights_init(&rights, CAP_SOCK_CLIENT),
	     &sp->fp, NULL, NULL);
     if(error)
	  return error;

     sp->soc = sp->fp->f_data;
     sp->td = td;
     isc_start_receiver(sp);

     return error;
}
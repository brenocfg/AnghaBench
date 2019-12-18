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
struct ciss_request {TYPE_1__* cr_sc; } ;
struct TYPE_2__ {int ciss_flags; } ;

/* Variables and functions */
 int CISS_FLAG_RUNNING ; 
 int ciss_poll_request (struct ciss_request*,int) ; 
 int ciss_wait_request (struct ciss_request*,int) ; 

__attribute__((used)) static int
ciss_synch_request(struct ciss_request *cr, int timeout)
{
    if (cr->cr_sc->ciss_flags & CISS_FLAG_RUNNING) {
	return(ciss_wait_request(cr, timeout));
    } else {
	return(ciss_poll_request(cr, timeout));
    }
}
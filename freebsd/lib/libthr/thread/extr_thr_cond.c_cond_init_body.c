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
struct pthread_cond_attr {int /*<<< orphan*/  c_clockid; scalar_t__ c_pshared; } ;
struct TYPE_2__ {int /*<<< orphan*/  c_clockid; int /*<<< orphan*/  c_flags; } ;
struct pthread_cond {TYPE_1__ kcond; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  USYNC_PROCESS_SHARED ; 

__attribute__((used)) static void
cond_init_body(struct pthread_cond *cvp, const struct pthread_cond_attr *cattr)
{

	if (cattr == NULL) {
		cvp->kcond.c_clockid = CLOCK_REALTIME;
	} else {
		if (cattr->c_pshared)
			cvp->kcond.c_flags |= USYNC_PROCESS_SHARED;
		cvp->kcond.c_clockid = cattr->c_clockid;
	}
}
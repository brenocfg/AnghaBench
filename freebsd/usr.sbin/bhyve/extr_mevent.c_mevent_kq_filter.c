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
struct mevent {scalar_t__ me_type; } ;

/* Variables and functions */
 int EVFILT_READ ; 
 int EVFILT_SIGNAL ; 
 int EVFILT_TIMER ; 
 int EVFILT_WRITE ; 
 scalar_t__ EVF_READ ; 
 scalar_t__ EVF_SIGNAL ; 
 scalar_t__ EVF_TIMER ; 
 scalar_t__ EVF_WRITE ; 

__attribute__((used)) static int
mevent_kq_filter(struct mevent *mevp)
{
	int retval;

	retval = 0;

	if (mevp->me_type == EVF_READ)
		retval = EVFILT_READ;

	if (mevp->me_type == EVF_WRITE)
		retval = EVFILT_WRITE;

	if (mevp->me_type == EVF_TIMER)
		retval = EVFILT_TIMER;

	if (mevp->me_type == EVF_SIGNAL)
		retval = EVFILT_SIGNAL;

	return (retval);
}
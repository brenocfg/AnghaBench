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
struct TYPE_3__ {int i_val; } ;
struct TYPE_4__ {int chan; int /*<<< orphan*/  last_hop; TYPE_1__ ireq; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCS80211 ; 
 TYPE_2__ chaninfo ; 
 int /*<<< orphan*/  die (int,char*) ; 
 int /*<<< orphan*/  display_chan () ; 
 int gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ioctl_s ; 

void set_chan(int c) {
        chaninfo.ireq.i_val = c;

        if (ioctl(ioctl_s, SIOCS80211, &chaninfo.ireq) == -1)
                die(1, "ioctl(SIOCS80211) [chan]");
        
	chaninfo.chan = c;

	if (gettimeofday(&chaninfo.last_hop, NULL) == -1)
		die(1, "gettimeofday()");

	display_chan();
}
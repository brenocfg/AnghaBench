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
struct TYPE_4__ {int chan; TYPE_1__ ireq; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCS80211 ; 
 TYPE_2__ chaninfo ; 
 int /*<<< orphan*/  exit (int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  perror (char*) ; 

void set_chan(int c) {
	if (c == chaninfo.chan)
		return;
	
	chaninfo.ireq.i_val = c;

	if (ioctl(chaninfo.s, SIOCS80211, &chaninfo.ireq) == -1) {
		perror("ioctl(SIOCS80211) [chan]");
		exit(1);
	}
	chaninfo.chan = c;
}
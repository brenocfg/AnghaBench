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
struct TYPE_2__ {scalar_t__ chan; scalar_t__ locked; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 TYPE_1__ chaninfo ; 
 int /*<<< orphan*/  exit (int) ; 
 int ioctl_s ; 
 int /*<<< orphan*/  perror (char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void init_globals() {
	ioctl_s = socket(PF_INET, SOCK_DGRAM, 0);
	if (ioctl_s == -1) {
		perror("socket()");
		exit(1);
	}

	chaninfo.locked = 0;
	chaninfo.chan = 0;
}
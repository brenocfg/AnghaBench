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
struct afswtch {int dummy; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_3__ {scalar_t__ ifr_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIFGOPTS ; 
 int /*<<< orphan*/  GIFSOPTS ; 
 TYPE_1__ ifr ; 
 int ioctl (int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
setgifopts(const char *val, int d, int s, const struct afswtch *afp)
{
	int opts;

	ifr.ifr_data = (caddr_t)&opts;
	if (ioctl(s, GIFGOPTS, &ifr) == -1) {
		warn("ioctl(GIFGOPTS)");
		return;
	}

	if (d < 0)
		opts &= ~(-d);
	else
		opts |= d;

	if (ioctl(s, GIFSOPTS, &ifr) == -1) {
		warn("ioctl(GIFSOPTS)");
		return;
	}
}
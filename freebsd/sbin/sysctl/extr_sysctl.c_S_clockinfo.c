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
struct clockinfo {int /*<<< orphan*/  stathz; int /*<<< orphan*/  profhz; int /*<<< orphan*/  tick; int /*<<< orphan*/  hz; } ;

/* Variables and functions */
 scalar_t__ hflag ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,size_t,int) ; 

__attribute__((used)) static int
S_clockinfo(size_t l2, void *p)
{
	struct clockinfo *ci = (struct clockinfo*)p;

	if (l2 != sizeof(*ci)) {
		warnx("S_clockinfo %zu != %zu", l2, sizeof(*ci));
		return (1);
	}
	printf(hflag ? "{ hz = %'d, tick = %'d, profhz = %'d, stathz = %'d }" :
		"{ hz = %d, tick = %d, profhz = %d, stathz = %d }",
		ci->hz, ci->tick, ci->profhz, ci->stathz);
	return (0);
}
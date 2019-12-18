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
struct TYPE_2__ {int /*<<< orphan*/  ifr_name; } ;
struct athaggrstatfoo_p {TYPE_1__ ifr; int /*<<< orphan*/  s; } ;
struct athaggrstatfoo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCZATHSTATS ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void 
ath_zerostats(struct athaggrstatfoo *wf0)
{
#if 0
	struct athaggrstatfoo_p *wf = (struct athaggrstatfoo_p *) wf0;

	if (ioctl(wf->s, SIOCZATHSTATS, &wf->ifr) < 0)
		err(-1, wf->ifr.ifr_name);
#endif
}
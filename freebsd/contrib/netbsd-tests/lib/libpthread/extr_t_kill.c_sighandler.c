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
typedef  scalar_t__ pthread_t ;
struct TYPE_2__ {scalar_t__ id; int /*<<< orphan*/  gotsignal; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*) ; 
 int NTHREAD ; 
 int SIGUSR1 ; 
 scalar_t__ mainthread ; 
 scalar_t__ pthread_self () ; 
 TYPE_1__* th ; 

__attribute__((used)) static void
sighandler(int signo)
{
	pthread_t self;
	int i;

	self = pthread_self();
	ATF_REQUIRE_MSG((self != mainthread) && (signo == SIGUSR1),
				  "unexpected signal");

	for (i = 0; i < NTHREAD; i++)
		if (self == th[i].id)
			break;

	ATF_REQUIRE_MSG(i != NTHREAD, "unknown thread");

	th[i].gotsignal++;
}
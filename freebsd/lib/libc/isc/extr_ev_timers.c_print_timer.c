#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_4__ {int /*<<< orphan*/  tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_6__ {TYPE_2__ inter; TYPE_1__ due; int /*<<< orphan*/  uap; int /*<<< orphan*/  func; } ;
typedef  TYPE_3__ evTimer ;
typedef  int /*<<< orphan*/  evContext_p ;

/* Variables and functions */
 int /*<<< orphan*/  evPrintf (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_timer(void *what, void *uap) {
	evTimer *cur = what;
	evContext_p *ctx = uap;

	cur = what;
	evPrintf(ctx, 7,
	    "  func %p, uap %p, due %ld.%09ld, inter %ld.%09ld\n",
		 cur->func, cur->uap,
		 (long)cur->due.tv_sec, cur->due.tv_nsec,
		 (long)cur->inter.tv_sec, cur->inter.tv_nsec);
}
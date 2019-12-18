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
struct aggent {int dummy; } ;

/* Variables and functions */
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct aggent* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct aggent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ag_fiter ; 
 int /*<<< orphan*/  fqueue ; 

__attribute__((used)) static void
fqueue_deleteall(void)
{
	struct aggent *agg;

	while (TAILQ_EMPTY(&fqueue) == 0) {
		agg = TAILQ_FIRST(&fqueue);
		TAILQ_REMOVE(&fqueue, agg, ag_fiter);
	}
}
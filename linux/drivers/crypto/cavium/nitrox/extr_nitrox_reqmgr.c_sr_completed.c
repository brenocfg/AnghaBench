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
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/ * completion; int /*<<< orphan*/ * orh; } ;
struct nitrox_softreq {TYPE_1__ resp; } ;

/* Variables and functions */
 int PENDING_SIG ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static bool sr_completed(struct nitrox_softreq *sr)
{
	u64 orh = READ_ONCE(*sr->resp.orh);
	unsigned long timeout = jiffies + msecs_to_jiffies(1);

	if ((orh != PENDING_SIG) && (orh & 0xff))
		return true;

	while (READ_ONCE(*sr->resp.completion) == PENDING_SIG) {
		if (time_after(jiffies, timeout)) {
			pr_err("comp not done\n");
			return false;
		}
	}

	return true;
}
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
struct admhcd {int /*<<< orphan*/  pending; int /*<<< orphan*/  lock; int /*<<< orphan*/  next_statechange; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void admhc_hcd_init(struct admhcd *ahcd)
{
	ahcd->next_statechange = jiffies;
	spin_lock_init(&ahcd->lock);
	INIT_LIST_HEAD(&ahcd->pending);
}
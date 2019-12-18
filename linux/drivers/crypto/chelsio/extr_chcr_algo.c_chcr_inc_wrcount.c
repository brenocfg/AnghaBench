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
struct chcr_dev {scalar_t__ state; int /*<<< orphan*/  inflight; } ;

/* Variables and functions */
 scalar_t__ CHCR_DETACH ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int chcr_inc_wrcount(struct chcr_dev *dev)
{
	if (dev->state == CHCR_DETACH)
		return 1;
	atomic_inc(&dev->inflight);
	return 0;
}
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
struct skd_device {int /*<<< orphan*/  tag_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_tagset_busy_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  skd_inc_in_flight ; 

__attribute__((used)) static int skd_in_flight(struct skd_device *skdev)
{
	int count = 0;

	blk_mq_tagset_busy_iter(&skdev->tag_set, skd_inc_in_flight, &count);

	return count;
}
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
struct bio {int /*<<< orphan*/  bio_classifier1; } ;

/* Variables and functions */
 int /*<<< orphan*/  curthread ; 

__attribute__((used)) static int
g_sched_tag(void *arg, struct bio *bp)
{

	bp->bio_classifier1 = curthread;
	return (1);
}
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
typedef  int /*<<< orphan*/  u_long ;
struct bio {scalar_t__ bio_classifier1; } ;

/* Variables and functions */

__attribute__((used)) static inline u_long
g_sched_classify(struct bio *bp)
{

	/* we have classifier fields in the struct bio */
	return ((u_long)bp->bio_classifier1);
}
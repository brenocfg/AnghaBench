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
struct gap_stats {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAPBLK_NONE ; 
 int /*<<< orphan*/  bzero (struct gap_stats*,int) ; 

__attribute__((used)) static inline void
init_gap_stats(struct gap_stats *stats)
{

	bzero(stats, sizeof(*stats));
	stats->start = SWAPBLK_NONE;
}
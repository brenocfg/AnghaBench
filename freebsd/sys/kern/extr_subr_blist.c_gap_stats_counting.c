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
struct gap_stats {scalar_t__ start; } ;

/* Variables and functions */
 scalar_t__ SWAPBLK_NONE ; 

__attribute__((used)) static inline bool
gap_stats_counting(const struct gap_stats *stats)
{

	return (stats->start != SWAPBLK_NONE);
}
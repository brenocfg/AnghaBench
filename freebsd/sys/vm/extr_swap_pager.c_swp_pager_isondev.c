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
struct swdevt {scalar_t__ sw_first; scalar_t__ sw_end; } ;
typedef  scalar_t__ daddr_t ;

/* Variables and functions */

__attribute__((used)) static bool
swp_pager_isondev(daddr_t blk, struct swdevt *sp)
{

	return (blk >= sp->sw_first && blk < sp->sw_end);
}
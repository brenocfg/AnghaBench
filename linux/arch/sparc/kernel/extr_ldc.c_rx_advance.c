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
struct ldc_channel {int /*<<< orphan*/  rx_num_entries; } ;

/* Variables and functions */
 unsigned long __advance (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long rx_advance(struct ldc_channel *lp, unsigned long off)
{
	return __advance(off, lp->rx_num_entries);
}
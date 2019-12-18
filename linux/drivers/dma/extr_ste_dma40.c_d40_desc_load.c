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
struct d40_desc {int /*<<< orphan*/  lli_len; int /*<<< orphan*/  lli_current; } ;
struct d40_chan {int dummy; } ;

/* Variables and functions */
 scalar_t__ chan_is_physical (struct d40_chan*) ; 
 int /*<<< orphan*/  d40_log_lli_to_lcxa (struct d40_chan*,struct d40_desc*) ; 
 int /*<<< orphan*/  d40_phy_lli_load (struct d40_chan*,struct d40_desc*) ; 

__attribute__((used)) static void d40_desc_load(struct d40_chan *d40c, struct d40_desc *d40d)
{
	if (chan_is_physical(d40c)) {
		d40_phy_lli_load(d40c, d40d);
		d40d->lli_current = d40d->lli_len;
	} else
		d40_log_lli_to_lcxa(d40c, d40d);
}
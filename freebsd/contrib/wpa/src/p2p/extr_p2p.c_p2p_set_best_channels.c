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
struct p2p_data {int best_freq_24; int best_freq_5; int best_freq_overall; } ;

/* Variables and functions */
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,int,int,int) ; 

void p2p_set_best_channels(struct p2p_data *p2p, int freq_24, int freq_5,
			   int freq_overall)
{
	p2p_dbg(p2p, "Best channel: 2.4 GHz: %d,  5 GHz: %d,  overall: %d",
		freq_24, freq_5, freq_overall);
	p2p->best_freq_24 = freq_24;
	p2p->best_freq_5 = freq_5;
	p2p->best_freq_overall = freq_overall;
}
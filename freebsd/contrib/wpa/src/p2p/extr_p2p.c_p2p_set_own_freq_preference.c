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
struct p2p_data {int own_freq_preference; } ;

/* Variables and functions */
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,int) ; 

void p2p_set_own_freq_preference(struct p2p_data *p2p, int freq)
{
	p2p_dbg(p2p, "Own frequency preference: %d MHz", freq);
	p2p->own_freq_preference = freq;
}
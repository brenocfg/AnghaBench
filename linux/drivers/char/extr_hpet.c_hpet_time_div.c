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
struct hpets {unsigned long hp_tick_freq; } ;

/* Variables and functions */
 unsigned long div64_ul (unsigned long long,unsigned long) ; 

__attribute__((used)) static inline unsigned long hpet_time_div(struct hpets *hpets,
					  unsigned long dis)
{
	unsigned long long m;

	m = hpets->hp_tick_freq + (dis >> 1);
	return div64_ul(m, dis);
}
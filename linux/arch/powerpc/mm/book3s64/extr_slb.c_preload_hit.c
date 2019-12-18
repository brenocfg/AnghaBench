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
struct thread_info {unsigned char slb_preload_nr; unsigned char slb_preload_tail; unsigned long* slb_preload_esid; } ;

/* Variables and functions */
 unsigned char SLB_PRELOAD_NR ; 

__attribute__((used)) static bool preload_hit(struct thread_info *ti, unsigned long esid)
{
	unsigned char i;

	for (i = 0; i < ti->slb_preload_nr; i++) {
		unsigned char idx;

		idx = (ti->slb_preload_tail + i) % SLB_PRELOAD_NR;
		if (esid == ti->slb_preload_esid[idx])
			return true;
	}
	return false;
}
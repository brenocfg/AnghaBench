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

/* Variables and functions */
 int /*<<< orphan*/  nlm_write_ucore_obufdone (unsigned int) ; 

__attribute__((used)) static __inline__ void
nlm_ucore_pkt_done(int l3cachelines, int fsv, int ffs, int prepad_en,
    int prepad_ovride, int prepad_size, int prepad0, int prepad1,
    int prepad2, int prepad3, int pkt_discard, int rd5)
{
	unsigned int val = 0;

	val |= ((l3cachelines & 0xfff) << 20);
	val |= ((fsv & 0x1) << 19);
	val |= ((ffs & 0x1f) << 14);
	val |= ((prepad_en & 0x1) << 3);
	val |= ((prepad_ovride & 0x1) << 2);
	val |= ((prepad_size & 0x3) << 12);
	val |= ((prepad0 & 0x3) << 4);
	val |= ((prepad1 & 0x3) << 6);
	val |= ((prepad2 & 0x3) << 8);
	val |= ((prepad3 & 0x3) << 10);
	val |= ((pkt_discard & 0x1) << 1);
	val |= ((rd5 & 0x1) << 0);

	nlm_write_ucore_obufdone(val);
}
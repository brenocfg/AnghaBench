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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  pt_ext_psb ; 
 int /*<<< orphan*/  pt_opc_psb ; 
 int /*<<< orphan*/  pt_psb_hi ; 
 int /*<<< orphan*/  pt_psb_lo ; 
 int pt_psb_repeat_count ; 

__attribute__((used)) static void sfix_encode_psb(uint8_t *pos)
{
	int i;

	*pos++ = pt_opc_psb;
	*pos++ = pt_ext_psb;

	for (i = 0; i < pt_psb_repeat_count; ++i) {
		*pos++ = pt_psb_hi;
		*pos++ = pt_psb_lo;
	}
}
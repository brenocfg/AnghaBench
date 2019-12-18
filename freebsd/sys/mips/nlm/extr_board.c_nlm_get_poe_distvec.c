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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int XLPGE_RX_VC ; 
 int /*<<< orphan*/  nlm_calc_poe_distvec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xlp_msg_thread_mask ; 

int
nlm_get_poe_distvec(int vec, uint32_t *distvec)
{

	if (vec != 0)
		return (-1);  /* we support just vec 0 */
	nlm_calc_poe_distvec(xlp_msg_thread_mask, 0, 0, 0,
	    0x1 << XLPGE_RX_VC, distvec);
	return (0);
}
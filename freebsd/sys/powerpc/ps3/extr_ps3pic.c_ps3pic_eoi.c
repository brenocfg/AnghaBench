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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int fls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lv1_end_of_interrupt_ext (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lv1_get_logical_ppe_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfctrl () ; 

__attribute__((used)) static void
ps3pic_eoi(device_t dev, u_int irq, void *priv)
{
	uint64_t ppe;
	int thread;

	lv1_get_logical_ppe_id(&ppe);
	thread = 32 - fls(mfctrl());

	lv1_end_of_interrupt_ext(ppe, thread, irq);
}
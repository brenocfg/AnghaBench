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
struct nicpf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nic_mbx_intr_handler (struct nicpf*,int) ; 

__attribute__((used)) static void
nic_mbx1_intr_handler (void *arg)
{
	struct nicpf *nic = (struct nicpf *)arg;

	nic_mbx_intr_handler(nic, 1);
}
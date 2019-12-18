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
struct fman_qmi_regs {int /*<<< orphan*/  fmqm_gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ *) ; 

uint8_t fman_get_qmi_deq_th(struct fman_qmi_regs *qmi_rg)
{
	return (uint8_t)ioread32be(&qmi_rg->fmqm_gc);
}
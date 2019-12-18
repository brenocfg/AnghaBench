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
struct ibmvtpm_dev {int dummy; } ;
struct ibmvtpm_crq {scalar_t__ valid; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct ibmvtpm_crq* ibmvtpm_crq_get_next (struct ibmvtpm_dev*) ; 
 int /*<<< orphan*/  ibmvtpm_crq_process (struct ibmvtpm_crq*,struct ibmvtpm_dev*) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static irqreturn_t ibmvtpm_interrupt(int irq, void *vtpm_instance)
{
	struct ibmvtpm_dev *ibmvtpm = (struct ibmvtpm_dev *) vtpm_instance;
	struct ibmvtpm_crq *crq;

	/* while loop is needed for initial setup (get version and
	 * get rtce_size). There should be only one tpm request at any
	 * given time.
	 */
	while ((crq = ibmvtpm_crq_get_next(ibmvtpm)) != NULL) {
		ibmvtpm_crq_process(crq, ibmvtpm);
		crq->valid = 0;
		smp_wmb();
	}

	return IRQ_HANDLED;
}
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
struct nvme_qpair {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_admin_qpair_abort_aers (struct nvme_qpair*) ; 
 int /*<<< orphan*/  nvme_qpair_disable (struct nvme_qpair*) ; 

void
nvme_admin_qpair_disable(struct nvme_qpair *qpair)
{

	nvme_qpair_disable(qpair);
	nvme_admin_qpair_abort_aers(qpair);
}
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
struct cptvf_wqe_info {struct cptvf_wqe* vq_wqe; } ;
struct cptvf_wqe {int /*<<< orphan*/  qno; int /*<<< orphan*/  cptvf; } ;

/* Variables and functions */
 int /*<<< orphan*/  vq_post_process (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vq_work_handler(unsigned long data)
{
	struct cptvf_wqe_info *cwqe_info = (struct cptvf_wqe_info *)data;
	struct cptvf_wqe *cwqe = &cwqe_info->vq_wqe[0];

	vq_post_process(cwqe->cptvf, cwqe->qno);
}
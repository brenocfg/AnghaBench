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
struct nvme_controller_data {int dummy; } ;
struct nvme_controller {struct nvme_controller_data const cdata; } ;

/* Variables and functions */

const struct nvme_controller_data *
nvme_ctrlr_get_data(struct nvme_controller *ctrlr)
{

	return (&ctrlr->cdata);
}
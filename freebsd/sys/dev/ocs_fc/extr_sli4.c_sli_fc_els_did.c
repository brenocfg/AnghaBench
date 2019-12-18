#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  sli4_t ;
struct TYPE_2__ {int wqe_specific_2; scalar_t__ status; } ;
typedef  TYPE_1__ sli4_fc_wcqe_t ;
typedef  int int32_t ;

/* Variables and functions */

int32_t
sli_fc_els_did(sli4_t *sli4, uint8_t *cqe, uint32_t *d_id)
{
	sli4_fc_wcqe_t *wcqe = (void *)cqe;

	*d_id = 0;

	if (wcqe->status) {
		return -1;
	} else {
		*d_id = wcqe->wqe_specific_2 & 0x00ffffff;
		return 0;
	}
}
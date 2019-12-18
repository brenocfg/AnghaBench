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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sli4_t ;
struct TYPE_2__ {int /*<<< orphan*/  wqe_specific_1; } ;
typedef  TYPE_1__ sli4_fc_wcqe_t ;

/* Variables and functions */

uint32_t
sli_fc_response_length(sli4_t *sli4, uint8_t *cqe)
{
	sli4_fc_wcqe_t *wcqe = (void *)cqe;

	return wcqe->wqe_specific_1;
}
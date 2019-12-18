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
struct tncc_data {struct tnc_if_imc* imc; } ;
struct tnc_if_imc {scalar_t__ imc_send_len; struct tnc_if_imc* next; } ;

/* Variables and functions */

size_t tncc_total_send_len(struct tncc_data *tncc)
{
	struct tnc_if_imc *imc;

	size_t len = 0;
	for (imc = tncc->imc; imc; imc = imc->next)
		len += imc->imc_send_len;
	return len;
}
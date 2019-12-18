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
typedef  int /*<<< orphan*/  u8 ;
struct tncc_data {struct tnc_if_imc* imc; } ;
struct tnc_if_imc {scalar_t__ imc_send_len; int /*<<< orphan*/ * imc_send; struct tnc_if_imc* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

u8 * tncc_copy_send_buf(struct tncc_data *tncc, u8 *pos)
{
	struct tnc_if_imc *imc;

	for (imc = tncc->imc; imc; imc = imc->next) {
		if (imc->imc_send == NULL)
			continue;

		os_memcpy(pos, imc->imc_send, imc->imc_send_len);
		pos += imc->imc_send_len;
		os_free(imc->imc_send);
		imc->imc_send = NULL;
		imc->imc_send_len = 0;
	}

	return pos;
}
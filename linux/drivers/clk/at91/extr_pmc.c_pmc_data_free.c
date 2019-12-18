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
struct pmc_data {int /*<<< orphan*/  ghws; int /*<<< orphan*/  phws; int /*<<< orphan*/  shws; int /*<<< orphan*/  chws; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void pmc_data_free(struct pmc_data *pmc_data)
{
	kfree(pmc_data->chws);
	kfree(pmc_data->shws);
	kfree(pmc_data->phws);
	kfree(pmc_data->ghws);
}
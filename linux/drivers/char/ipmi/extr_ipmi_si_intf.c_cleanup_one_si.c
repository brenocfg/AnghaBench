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
struct smi_info {scalar_t__ intf; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipmi_unregister_smi (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct smi_info*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cleanup_one_si(struct smi_info *smi_info)
{
	if (!smi_info)
		return;

	list_del(&smi_info->link);

	if (smi_info->intf)
		ipmi_unregister_smi(smi_info->intf);

	kfree(smi_info);
}
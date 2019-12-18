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
typedef  int /*<<< orphan*/  u32 ;
struct altera_cvp_conf {scalar_t__ vsec_offset; int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 scalar_t__ VSE_CVP_DATA ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void altera_cvp_write_data_config(struct altera_cvp_conf *conf, u32 val)
{
	pci_write_config_dword(conf->pci_dev, conf->vsec_offset + VSE_CVP_DATA,
			       val);
}
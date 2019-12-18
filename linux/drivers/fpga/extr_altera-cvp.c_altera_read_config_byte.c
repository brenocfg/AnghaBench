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
struct altera_cvp_conf {scalar_t__ vsec_offset; int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int pci_read_config_byte (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int altera_read_config_byte(struct altera_cvp_conf *conf,
				   int where, u8 *val)
{
	return pci_read_config_byte(conf->pci_dev, conf->vsec_offset + where,
				    val);
}
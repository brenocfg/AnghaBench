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
struct uli_priv {unsigned int* scr_cfg_addr; } ;
struct ata_port {size_t port_no; TYPE_1__* host; } ;
struct TYPE_2__ {struct uli_priv* private_data; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int get_scr_cfg_addr(struct ata_port *ap, unsigned int sc_reg)
{
	struct uli_priv *hpriv = ap->host->private_data;
	return hpriv->scr_cfg_addr[ap->port_no] + (4 * sc_reg);
}
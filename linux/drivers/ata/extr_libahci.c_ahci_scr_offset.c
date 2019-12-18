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
struct ata_port {TYPE_1__* host; } ;
struct ahci_host_priv {int cap; } ;
struct TYPE_2__ {struct ahci_host_priv* private_data; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int const*) ; 
 int HOST_CAP_SNTF ; 
#define  PORT_SCR_ACT 137 
#define  PORT_SCR_CTL 136 
#define  PORT_SCR_ERR 135 
#define  PORT_SCR_NTF 134 
#define  PORT_SCR_STAT 133 
#define  SCR_ACTIVE 132 
#define  SCR_CONTROL 131 
#define  SCR_ERROR 130 
#define  SCR_NOTIFICATION 129 
#define  SCR_STATUS 128 

__attribute__((used)) static unsigned ahci_scr_offset(struct ata_port *ap, unsigned int sc_reg)
{
	static const int offset[] = {
		[SCR_STATUS]		= PORT_SCR_STAT,
		[SCR_CONTROL]		= PORT_SCR_CTL,
		[SCR_ERROR]		= PORT_SCR_ERR,
		[SCR_ACTIVE]		= PORT_SCR_ACT,
		[SCR_NOTIFICATION]	= PORT_SCR_NTF,
	};
	struct ahci_host_priv *hpriv = ap->host->private_data;

	if (sc_reg < ARRAY_SIZE(offset) &&
	    (sc_reg != SCR_NOTIFICATION || (hpriv->cap & HOST_CAP_SNTF)))
		return offset[sc_reg];
	return 0;
}
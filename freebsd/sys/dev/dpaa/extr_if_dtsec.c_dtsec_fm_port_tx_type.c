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
typedef  enum eth_dev_type { ____Placeholder_eth_dev_type } eth_dev_type ;
typedef  int /*<<< orphan*/  e_FmPortType ;

/* Variables and functions */
#define  ETH_10GSEC 129 
#define  ETH_DTSEC 128 
 int /*<<< orphan*/  e_FM_PORT_TYPE_DUMMY ; 
 int /*<<< orphan*/  e_FM_PORT_TYPE_TX ; 
 int /*<<< orphan*/  e_FM_PORT_TYPE_TX_10G ; 

e_FmPortType
dtsec_fm_port_tx_type(enum eth_dev_type type)
{

	switch (type) {
	case ETH_DTSEC:
		return (e_FM_PORT_TYPE_TX);
	case ETH_10GSEC:
		return (e_FM_PORT_TYPE_TX_10G);
	default:
		return (e_FM_PORT_TYPE_DUMMY);
	}
}
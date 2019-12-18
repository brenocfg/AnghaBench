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
struct resource {int dummy; } ;
typedef  int pci_addr_t ;

/* Variables and functions */
 int NIC_NODE_ID_MASK ; 
 int NIC_NODE_ID_SHIFT ; 
 int rman_get_start (struct resource*) ; 

__attribute__((used)) static __inline int
nic_get_node_id(struct resource *res)
{
	pci_addr_t addr;

	addr = rman_get_start(res);
	return ((addr >> NIC_NODE_ID_SHIFT) & NIC_NODE_ID_MASK);
}
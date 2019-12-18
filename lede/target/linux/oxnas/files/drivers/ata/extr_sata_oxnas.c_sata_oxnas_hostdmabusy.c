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
typedef  int u32 ;
struct sata_oxnas_port_priv {scalar_t__ sgdma_base; } ;
struct ata_port {struct sata_oxnas_port_priv* private_data; } ;

/* Variables and functions */
 int SGDMA_BUSY ; 
 scalar_t__ SGDMA_STATUS ; 
 int ioread32 (scalar_t__) ; 

__attribute__((used)) static inline u32 sata_oxnas_hostdmabusy(struct ata_port *ap)
{
	struct sata_oxnas_port_priv *pd = ap->private_data;

	return ioread32(pd->sgdma_base + SGDMA_STATUS) & SGDMA_BUSY;
}
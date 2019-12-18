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
typedef  int u8 ;
struct cns3xxx_spi {int dummy; } ;

/* Variables and functions */
 int SPI_INTERRUPT_STATUS_REG ; 

__attribute__((used)) static inline u8 cns3xxx_spi_tx_buffer_empty(struct cns3xxx_spi *hw)
{
	return ((SPI_INTERRUPT_STATUS_REG & (0x1 << 3)) ? 1 : 0);
}
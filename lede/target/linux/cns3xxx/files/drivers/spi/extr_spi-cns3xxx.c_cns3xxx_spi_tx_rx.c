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
typedef  int /*<<< orphan*/  u32 ;
struct cns3xxx_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_RECEIVE_BUFFER_REG ; 
 int SPI_RECEIVE_CONTROL_REG ; 
 int /*<<< orphan*/  SPI_TRANSMIT_BUFFER_REG ; 
 int SPI_TRANSMIT_CONTROL_REG ; 
 int /*<<< orphan*/  cns3xxx_spi_bus_idle (struct cns3xxx_spi*) ; 
 int /*<<< orphan*/  cns3xxx_spi_rx_buffer_full (struct cns3xxx_spi*) ; 
 int /*<<< orphan*/  cns3xxx_spi_tx_buffer_empty (struct cns3xxx_spi*) ; 

u8 cns3xxx_spi_tx_rx(struct cns3xxx_spi *hw, u8 tx_channel, u8 tx_eof,
		     u32 tx_data, u32 * rx_data)
{
	u8 rx_channel;
	u8 rx_eof;

	while (!cns3xxx_spi_bus_idle(hw)) ;	// do nothing

	while (!cns3xxx_spi_tx_buffer_empty(hw)) ;	// do nothing

	SPI_TRANSMIT_CONTROL_REG &= ~(0x7);
	SPI_TRANSMIT_CONTROL_REG |= (tx_channel & 0x3) | ((tx_eof & 0x1) << 2);

	SPI_TRANSMIT_BUFFER_REG = tx_data;

	while (!cns3xxx_spi_rx_buffer_full(hw)) ;	// do nothing

	rx_channel = SPI_RECEIVE_CONTROL_REG & 0x3;
	rx_eof = (SPI_RECEIVE_CONTROL_REG & (0x1 << 2)) ? 1 : 0;

	*rx_data = SPI_RECEIVE_BUFFER_REG;

	if ((tx_channel != rx_channel) || (tx_eof != rx_eof)) {
		return 0;
	} else {
		return 1;
	}
}
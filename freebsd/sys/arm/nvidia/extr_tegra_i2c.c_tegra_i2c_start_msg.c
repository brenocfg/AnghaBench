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
typedef  int uint32_t ;
struct tegra_i2c_softc {int dummy; } ;
struct iic_msg {int len; int slave; int flags; } ;
typedef  enum tegra_i2c_xfer_type { ____Placeholder_tegra_i2c_xfer_type } tegra_i2c_xfer_type ;

/* Variables and functions */
 int I2C_HEADER_CONTINUE_XFER ; 
 int I2C_HEADER_IE_ENABLE ; 
 int I2C_HEADER_READ ; 
 int I2C_HEADER_REPEAT_START ; 
 int I2C_HEADER_SLAVE_ADDR_SHIFT ; 
 int /*<<< orphan*/  I2C_INTERRUPT_MASK_REGISTER ; 
 int I2C_INT_ARB_LOST ; 
 int I2C_INT_NOACK ; 
 int I2C_INT_PACKET_XFER_COMPLETE ; 
 int I2C_INT_RFIFO_DATA_REQ ; 
 int I2C_INT_TFIFO_DATA_REQ ; 
 int /*<<< orphan*/  I2C_TX_PACKET_FIFO ; 
 int IIC_M_RD ; 
 int PACKET_HEADER0_CONT_ID_SHIFT ; 
 int PACKET_HEADER0_HEADER_SIZE_SHIFT ; 
 int PACKET_HEADER0_PACKET_ID_SHIFT ; 
 int PACKET_HEADER0_PROTOCOL_I2C ; 
 int /*<<< orphan*/  WR4 (struct tegra_i2c_softc*,int /*<<< orphan*/ ,int) ; 
 int XFER_CONTINUE ; 
 int XFER_REPEAT_START ; 

__attribute__((used)) static void
tegra_i2c_start_msg(struct tegra_i2c_softc *sc, struct iic_msg *msg,
    enum tegra_i2c_xfer_type xtype)
{
	uint32_t tmp, mask;

	/* Packet header. */
	tmp =  (0 << PACKET_HEADER0_HEADER_SIZE_SHIFT) |
	   PACKET_HEADER0_PROTOCOL_I2C |
	   (1 << PACKET_HEADER0_CONT_ID_SHIFT) |
	   (1 << PACKET_HEADER0_PACKET_ID_SHIFT);
	WR4(sc, I2C_TX_PACKET_FIFO, tmp);


	/* Packet size. */
	WR4(sc, I2C_TX_PACKET_FIFO, msg->len - 1);

	/* I2C header. */
	tmp = I2C_HEADER_IE_ENABLE;
	if (xtype == XFER_CONTINUE)
		tmp |= I2C_HEADER_CONTINUE_XFER;
	else if (xtype == XFER_REPEAT_START)
		tmp |= I2C_HEADER_REPEAT_START;
	tmp |= msg->slave << I2C_HEADER_SLAVE_ADDR_SHIFT;
	if (msg->flags & IIC_M_RD) {
		tmp |= I2C_HEADER_READ;
		tmp |= 1 << I2C_HEADER_SLAVE_ADDR_SHIFT;
	} else
		tmp &= ~(1 << I2C_HEADER_SLAVE_ADDR_SHIFT);

	WR4(sc, I2C_TX_PACKET_FIFO, tmp);

	/* Interrupt mask. */
	mask = I2C_INT_NOACK | I2C_INT_ARB_LOST | I2C_INT_PACKET_XFER_COMPLETE;
	if (msg->flags & IIC_M_RD)
		mask |= I2C_INT_RFIFO_DATA_REQ;
	else
		mask |= I2C_INT_TFIFO_DATA_REQ;
	WR4(sc, I2C_INTERRUPT_MASK_REGISTER, mask);
}
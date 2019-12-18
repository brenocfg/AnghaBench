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
typedef  int /*<<< orphan*/  ig4iic_softc_t ;

/* Variables and functions */
 int IG4_ABRTSRC_ACKED_START ; 
 int IG4_ABRTSRC_ARBLOST ; 
 int IG4_ABRTSRC_GENCALL_NOACK ; 
 int IG4_ABRTSRC_GENCALL_READ ; 
 int IG4_ABRTSRC_NORESTART_10 ; 
 int IG4_ABRTSRC_NORESTART_START ; 
 int IG4_ABRTSRC_TRANSFER ; 
 int IG4_ABRTSRC_TXNOACK_ADDR10_1 ; 
 int IG4_ABRTSRC_TXNOACK_ADDR10_2 ; 
 int IG4_ABRTSRC_TXNOACK_ADDR7 ; 
 int IG4_ABRTSRC_TXNOACK_DATA ; 
 int IG4_INTR_RX_OVER ; 
 int IG4_INTR_RX_UNDER ; 
 int IG4_INTR_TX_ABRT ; 
 int IG4_INTR_TX_OVER ; 
 int /*<<< orphan*/  IG4_REG_CLR_RX_OVER ; 
 int /*<<< orphan*/  IG4_REG_CLR_RX_UNDER ; 
 int /*<<< orphan*/  IG4_REG_CLR_TX_ABORT ; 
 int /*<<< orphan*/  IG4_REG_CLR_TX_OVER ; 
 int /*<<< orphan*/  IG4_REG_TX_ABRT_SOURCE ; 
 int IIC_EBUSBSY ; 
 int IIC_EBUSERR ; 
 int IIC_ENOACK ; 
 int IIC_ENOTSUPP ; 
 int IIC_EOVERFLOW ; 
 int IIC_ESTATUS ; 
 int IIC_EUNDERFLOW ; 
 int IIC_NOERR ; 
 int reg_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
intrstat2iic(ig4iic_softc_t *sc, uint32_t val)
{
	uint32_t src;

	if (val & IG4_INTR_RX_UNDER)
		reg_read(sc, IG4_REG_CLR_RX_UNDER);
	if (val & IG4_INTR_RX_OVER)
		reg_read(sc, IG4_REG_CLR_RX_OVER);
	if (val & IG4_INTR_TX_OVER)
		reg_read(sc, IG4_REG_CLR_TX_OVER);

	if (val & IG4_INTR_TX_ABRT) {
		src = reg_read(sc, IG4_REG_TX_ABRT_SOURCE);
		reg_read(sc, IG4_REG_CLR_TX_ABORT);
		/* User-requested abort. Not really a error */
		if (src & IG4_ABRTSRC_TRANSFER)
			return (IIC_ESTATUS);
		/* Master has lost arbitration */
		if (src & IG4_ABRTSRC_ARBLOST)
			return (IIC_EBUSBSY);
		/* Did not receive an acknowledge from the remote slave */
		if (src & (IG4_ABRTSRC_TXNOACK_ADDR7 |
			   IG4_ABRTSRC_TXNOACK_ADDR10_1 |
			   IG4_ABRTSRC_TXNOACK_ADDR10_2 |
			   IG4_ABRTSRC_TXNOACK_DATA |
			   IG4_ABRTSRC_GENCALL_NOACK))
			return (IIC_ENOACK);
		/* Programming errors */
		if (src & (IG4_ABRTSRC_GENCALL_READ |
			   IG4_ABRTSRC_NORESTART_START |
			   IG4_ABRTSRC_NORESTART_10))
			return (IIC_ENOTSUPP);
		/* Other errors */
		if (src & IG4_ABRTSRC_ACKED_START)
			return (IIC_EBUSERR);
	}
	/*
	 * TX_OVER, RX_OVER and RX_UNDER are caused by wrong RX/TX FIFO depth
	 * detection or driver's read/write pipelining errors.
	 */
	if (val & (IG4_INTR_TX_OVER | IG4_INTR_RX_OVER))
		return (IIC_EOVERFLOW);
	if (val & IG4_INTR_RX_UNDER)
		return (IIC_EUNDERFLOW);

	return (IIC_NOERR);
}
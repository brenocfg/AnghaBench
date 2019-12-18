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
typedef  int uint8_t ;
struct s390rtc_softc {int sc_addr; } ;
struct iic_msg {int slave; size_t len; int* buf; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IIC_M_WR ; 
 int /*<<< orphan*/  IIC_WAIT ; 
 int bitreverse (int) ; 
 struct s390rtc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int iicbus_transfer_excl (int /*<<< orphan*/ ,struct iic_msg*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
s390rtc_write(device_t dev, uint8_t reg, uint8_t *buf, size_t len)
{
	struct s390rtc_softc *sc = device_get_softc(dev);
	struct iic_msg msg[] = {
		{
			.slave = sc->sc_addr | reg,
			.flags = IIC_M_WR,
			.len = len,
			.buf = buf,
		},
	};
	int i;

	/* this chip expects each byte in reverse order */
	for (i = 0; i < len; ++i)
		buf[i] = bitreverse(buf[i]);

	return (iicbus_transfer_excl(dev, msg, 1, IIC_WAIT));
}
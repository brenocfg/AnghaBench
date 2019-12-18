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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct udl_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDL_CTRL_CMD_READ_1 ; 
 int USB_ERR_NORMAL_COMPLETION ; 
 int /*<<< orphan*/  UT_READ_VENDOR_DEVICE ; 
 int udl_ctrl_msg (struct udl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
udl_read_1(struct udl_softc *sc, uint16_t addr, uint8_t *buf)
{
	uint8_t lbuf[1];
	int error;

	error = udl_ctrl_msg(sc, UT_READ_VENDOR_DEVICE,
	    UDL_CTRL_CMD_READ_1, addr, 0x0000, lbuf, 1);
	if (error == USB_ERR_NORMAL_COMPLETION)
		*buf = *(uint8_t *)lbuf;
	return (error);
}
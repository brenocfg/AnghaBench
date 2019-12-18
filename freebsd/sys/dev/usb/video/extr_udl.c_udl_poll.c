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
typedef  int /*<<< orphan*/  uint32_t ;
struct udl_softc {int dummy; } ;
typedef  int /*<<< orphan*/  lbuf ;

/* Variables and functions */
 int /*<<< orphan*/  UDL_CTRL_CMD_POLL ; 
 int USB_ERR_NORMAL_COMPLETION ; 
 int /*<<< orphan*/  UT_READ_VENDOR_DEVICE ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 
 int udl_ctrl_msg (struct udl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
udl_poll(struct udl_softc *sc, uint32_t *buf)
{
	uint32_t lbuf;
	int error;

	error = udl_ctrl_msg(sc, UT_READ_VENDOR_DEVICE,
	    UDL_CTRL_CMD_POLL, 0x0000, 0x0000, (uint8_t *)&lbuf, sizeof(lbuf));
	if (error == USB_ERR_NORMAL_COMPLETION)
		*buf = le32toh(lbuf);
	return (error);
}
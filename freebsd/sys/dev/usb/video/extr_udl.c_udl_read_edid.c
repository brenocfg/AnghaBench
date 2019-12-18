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
typedef  int uint16_t ;
struct udl_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDL_CTRL_CMD_READ_EDID ; 
 int USB_ERR_NORMAL_COMPLETION ; 
 int /*<<< orphan*/  UT_READ_VENDOR_DEVICE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int udl_ctrl_msg (struct udl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
udl_read_edid(struct udl_softc *sc, uint8_t *buf)
{
	uint8_t lbuf[64];
	uint16_t offset;
	int error;

	offset = 0;

	error = udl_ctrl_msg(sc, UT_READ_VENDOR_DEVICE,
	    UDL_CTRL_CMD_READ_EDID, 0x00a1, (offset << 8), lbuf, 64);
	if (error != USB_ERR_NORMAL_COMPLETION)
		goto fail;
	bcopy(lbuf + 1, buf + offset, 63);
	offset += 63;

	error = udl_ctrl_msg(sc, UT_READ_VENDOR_DEVICE,
	    UDL_CTRL_CMD_READ_EDID, 0x00a1, (offset << 8), lbuf, 64);
	if (error != USB_ERR_NORMAL_COMPLETION)
		goto fail;
	bcopy(lbuf + 1, buf + offset, 63);
	offset += 63;

	error = udl_ctrl_msg(sc, UT_READ_VENDOR_DEVICE,
	    UDL_CTRL_CMD_READ_EDID, 0x00a1, (offset << 8), lbuf, 3);
	if (error != USB_ERR_NORMAL_COMPLETION)
		goto fail;
	bcopy(lbuf + 1, buf + offset, 2);
fail:
	return (error);
}
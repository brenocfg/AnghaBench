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
struct udl_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDL_CTRL_CMD_SET_KEY ; 
 int /*<<< orphan*/  UT_WRITE_VENDOR_DEVICE ; 
 int udl_ctrl_msg (struct udl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
udl_set_enc_key(struct udl_softc *sc, uint8_t *buf, uint8_t len)
{
	int error;

	error = udl_ctrl_msg(sc, UT_WRITE_VENDOR_DEVICE,
	    UDL_CTRL_CMD_SET_KEY, 0x0000, 0x0000, buf, len);
	return (error);
}
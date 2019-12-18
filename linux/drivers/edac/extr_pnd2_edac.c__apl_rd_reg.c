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
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int /*<<< orphan*/  P2SB_ADDR_OFF ; 
 int P2SB_BUSY ; 
 int /*<<< orphan*/  P2SB_DATA_OFF ; 
 int /*<<< orphan*/  P2SB_EADD_OFF ; 
 int /*<<< orphan*/  P2SB_HIDE_OFF ; 
 int /*<<< orphan*/  P2SB_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  P2SB_ROUT_OFF ; 
 int /*<<< orphan*/  P2SB_STAT_OFF ; 
 int /*<<< orphan*/  P2SB_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  byte ; 
 int /*<<< orphan*/  dword ; 
 scalar_t__ p2sb_is_busy (int*) ; 
 int /*<<< orphan*/  word ; 

__attribute__((used)) static int _apl_rd_reg(int port, int off, int op, u32 *data)
{
	int retries = 0xff, ret;
	u16 status;
	u8 hidden;

	/* Unhide the P2SB device, if it's hidden */
	P2SB_READ(byte, P2SB_HIDE_OFF, &hidden);
	if (hidden)
		P2SB_WRITE(byte, P2SB_HIDE_OFF, 0);

	if (p2sb_is_busy(&status)) {
		ret = -EAGAIN;
		goto out;
	}

	P2SB_WRITE(dword, P2SB_ADDR_OFF, (port << 24) | off);
	P2SB_WRITE(dword, P2SB_DATA_OFF, 0);
	P2SB_WRITE(dword, P2SB_EADD_OFF, 0);
	P2SB_WRITE(word, P2SB_ROUT_OFF, 0);
	P2SB_WRITE(word, P2SB_STAT_OFF, (op << 8) | P2SB_BUSY);

	while (p2sb_is_busy(&status)) {
		if (retries-- == 0) {
			ret = -EBUSY;
			goto out;
		}
	}

	P2SB_READ(dword, P2SB_DATA_OFF, data);
	ret = (status >> 1) & 0x3;
out:
	/* Hide the P2SB device, if it was hidden before */
	if (hidden)
		P2SB_WRITE(byte, P2SB_HIDE_OFF, hidden);

	return ret;
}
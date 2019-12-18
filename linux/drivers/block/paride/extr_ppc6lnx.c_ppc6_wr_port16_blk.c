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
typedef  int /*<<< orphan*/  Interface ;

/* Variables and functions */
 int ACCESS_PORT ; 
 int ACCESS_REG ; 
 int ACCESS_WRITE ; 
 int CMD_PREFIX_RESET ; 
 int CMD_PREFIX_SET ; 
 int PREFIX_BLK ; 
 int PREFIX_IO16 ; 
 int REG_BLKSIZE ; 
 int /*<<< orphan*/  ppc6_send_cmd (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ppc6_wr_data_blk (int /*<<< orphan*/ *,int*,long) ; 
 int /*<<< orphan*/  ppc6_wr_data_byte (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ppc6_wr_port16_blk(Interface *ppc, u8 port, u8 *data, long length)
{
	length = length << 1;

	ppc6_send_cmd(ppc, (REG_BLKSIZE | ACCESS_REG | ACCESS_WRITE));
	ppc6_wr_data_byte(ppc,(u8)length);
	ppc6_wr_data_byte(ppc,(u8)(length >> 8));
	ppc6_wr_data_byte(ppc,0);

	ppc6_send_cmd(ppc, (CMD_PREFIX_SET | PREFIX_IO16 | PREFIX_BLK));

	ppc6_send_cmd(ppc, (u8)(port | ACCESS_PORT | ACCESS_WRITE));

	ppc6_wr_data_blk(ppc, data, length);

	ppc6_send_cmd(ppc, (CMD_PREFIX_RESET | PREFIX_IO16 | PREFIX_BLK));
}
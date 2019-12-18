#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct request {int /*<<< orphan*/  bio; } ;
struct packet_command {int* cmd; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {int pending; int transfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  GDROM_BCH_REG ; 
 int /*<<< orphan*/  GDROM_BCL_REG ; 
 int GDROM_COM_PACKET ; 
 int /*<<< orphan*/  GDROM_DATA_REG ; 
 int /*<<< orphan*/  GDROM_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  GDROM_DMA_DIRECTION_REG ; 
 int /*<<< orphan*/  GDROM_DMA_ENABLE_REG ; 
 int /*<<< orphan*/  GDROM_DMA_LENGTH_REG ; 
 int /*<<< orphan*/  GDROM_DMA_STARTADDR_REG ; 
 int /*<<< orphan*/  GDROM_DMA_STATUS_REG ; 
 int /*<<< orphan*/  GDROM_DSEL_REG ; 
 int /*<<< orphan*/  GDROM_ERROR_REG ; 
 int GDROM_HARD_SECTOR ; 
 int /*<<< orphan*/  GDROM_INTSEC_REG ; 
 int /*<<< orphan*/  GDROM_SECNUM_REG ; 
 int /*<<< orphan*/  GDROM_STATUSCOMMAND_REG ; 
 int GD_SESSION_OFFSET ; 
 int GD_TO_BLK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 scalar_t__ __raw_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 int blk_rq_pos (struct request*) ; 
 int blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 TYPE_1__ gd ; 
 scalar_t__ gdrom_is_busy () ; 
 int jiffies ; 
 int /*<<< orphan*/  kfree (struct packet_command*) ; 
 struct packet_command* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outsw (int /*<<< orphan*/ ,int**,int) ; 
 int /*<<< orphan*/  request_queue ; 
 scalar_t__ time_before (int,unsigned long) ; 
 int virt_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static blk_status_t gdrom_readdisk_dma(struct request *req)
{
	int block, block_cnt;
	blk_status_t err;
	struct packet_command *read_command;
	unsigned long timeout;

	read_command = kzalloc(sizeof(struct packet_command), GFP_KERNEL);
	if (!read_command)
		return BLK_STS_RESOURCE;

	read_command->cmd[0] = 0x30;
	read_command->cmd[1] = 0x20;
	block = blk_rq_pos(req)/GD_TO_BLK + GD_SESSION_OFFSET;
	block_cnt = blk_rq_sectors(req)/GD_TO_BLK;
	__raw_writel(virt_to_phys(bio_data(req->bio)), GDROM_DMA_STARTADDR_REG);
	__raw_writel(block_cnt * GDROM_HARD_SECTOR, GDROM_DMA_LENGTH_REG);
	__raw_writel(1, GDROM_DMA_DIRECTION_REG);
	__raw_writel(1, GDROM_DMA_ENABLE_REG);
	read_command->cmd[2] = (block >> 16) & 0xFF;
	read_command->cmd[3] = (block >> 8) & 0xFF;
	read_command->cmd[4] = block & 0xFF;
	read_command->cmd[8] = (block_cnt >> 16) & 0xFF;
	read_command->cmd[9] = (block_cnt >> 8) & 0xFF;
	read_command->cmd[10] = block_cnt & 0xFF;
	/* set for DMA */
	__raw_writeb(1, GDROM_ERROR_REG);
	/* other registers */
	__raw_writeb(0, GDROM_SECNUM_REG);
	__raw_writeb(0, GDROM_BCL_REG);
	__raw_writeb(0, GDROM_BCH_REG);
	__raw_writeb(0, GDROM_DSEL_REG);
	__raw_writeb(0, GDROM_INTSEC_REG);
	/* Wait for registers to reset after any previous activity */
	timeout = jiffies + HZ / 2;
	while (gdrom_is_busy() && time_before(jiffies, timeout))
		cpu_relax();
	__raw_writeb(GDROM_COM_PACKET, GDROM_STATUSCOMMAND_REG);
	timeout = jiffies + HZ / 2;
	/* Wait for packet command to finish */
	while (gdrom_is_busy() && time_before(jiffies, timeout))
		cpu_relax();
	gd.pending = 1;
	gd.transfer = 1;
	outsw(GDROM_DATA_REG, &read_command->cmd, 6);
	timeout = jiffies + HZ / 2;
	/* Wait for any pending DMA to finish */
	while (__raw_readb(GDROM_DMA_STATUS_REG) &&
		time_before(jiffies, timeout))
		cpu_relax();
	/* start transfer */
	__raw_writeb(1, GDROM_DMA_STATUS_REG);
	wait_event_interruptible_timeout(request_queue,
		gd.transfer == 0, GDROM_DEFAULT_TIMEOUT);
	err = gd.transfer ? BLK_STS_IOERR : BLK_STS_OK;
	gd.transfer = 0;
	gd.pending = 0;

	blk_mq_end_request(req, err);
	kfree(read_command);
	return BLK_STS_OK;
}
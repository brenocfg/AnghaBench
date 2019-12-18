#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ep93xx_pata_data {int dummy; } ;
struct ata_queued_cmd {TYPE_2__* dev; } ;
struct ata_port {TYPE_3__* host; } ;
struct TYPE_6__ {struct ep93xx_pata_data* private_data; } ;
struct TYPE_5__ {TYPE_1__* link; } ;
struct TYPE_4__ {struct ata_port* ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDECTRL_ADDR_DATA ; 
 int READ ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep93xx_pata_read_data (struct ep93xx_pata_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep93xx_pata_write_data (struct ep93xx_pata_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (unsigned char) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static unsigned int ep93xx_pata_data_xfer(struct ata_queued_cmd *qc,
					  unsigned char *buf,
					  unsigned int buflen, int rw)
{
	struct ata_port *ap = qc->dev->link->ap;
	struct ep93xx_pata_data *drv_data = ap->host->private_data;
	u16 *data = (u16 *)buf;
	unsigned int words = buflen >> 1;

	/* Transfer multiple of 2 bytes */
	while (words--)
		if (rw == READ)
			*data++ = cpu_to_le16(
				ep93xx_pata_read_data(
					drv_data, IDECTRL_ADDR_DATA));
		else
			ep93xx_pata_write_data(drv_data, le16_to_cpu(*data++),
				IDECTRL_ADDR_DATA);

	/* Transfer trailing 1 byte, if any. */
	if (unlikely(buflen & 0x01)) {
		unsigned char pad[2] = { };

		buf += buflen - 1;

		if (rw == READ) {
			*pad = cpu_to_le16(
				ep93xx_pata_read_data(
					drv_data, IDECTRL_ADDR_DATA));
			*buf = pad[0];
		} else {
			pad[0] = *buf;
			ep93xx_pata_write_data(drv_data, le16_to_cpu(*pad),
					  IDECTRL_ADDR_DATA);
		}
		words++;
	}

	return words << 1;
}
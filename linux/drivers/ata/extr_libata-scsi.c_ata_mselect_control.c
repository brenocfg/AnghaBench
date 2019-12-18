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
typedef  int u16 ;
struct ata_queued_cmd {struct ata_device* dev; } ;
struct ata_device {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DFLAG_D_SENSE ; 
 int CONTROL_MPAGE_LEN ; 
 int EINVAL ; 
 int /*<<< orphan*/  ata_msense_control (struct ata_device*,int*,int) ; 

__attribute__((used)) static int ata_mselect_control(struct ata_queued_cmd *qc,
			       const u8 *buf, int len, u16 *fp)
{
	struct ata_device *dev = qc->dev;
	u8 mpage[CONTROL_MPAGE_LEN];
	u8 d_sense;
	int i;

	/*
	 * The first two bytes of def_control_mpage are a header, so offsets
	 * in mpage are off by 2 compared to buf.  Same for len.
	 */

	if (len != CONTROL_MPAGE_LEN - 2) {
		if (len < CONTROL_MPAGE_LEN - 2)
			*fp = len;
		else
			*fp = CONTROL_MPAGE_LEN - 2;
		return -EINVAL;
	}

	d_sense = buf[0] & (1 << 2);

	/*
	 * Check that read-only bits are not modified.
	 */
	ata_msense_control(dev, mpage, false);
	for (i = 0; i < CONTROL_MPAGE_LEN - 2; i++) {
		if (i == 0)
			continue;
		if (mpage[2 + i] != buf[i]) {
			*fp = i;
			return -EINVAL;
		}
	}
	if (d_sense & (1 << 2))
		dev->flags |= ATA_DFLAG_D_SENSE;
	else
		dev->flags &= ~ATA_DFLAG_D_SENSE;
	return 0;
}
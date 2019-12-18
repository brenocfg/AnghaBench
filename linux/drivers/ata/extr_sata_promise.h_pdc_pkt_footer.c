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
struct ata_taskfile {int flags; int device; int command; } ;

/* Variables and functions */
 int ATA_REG_CMD ; 
 int ATA_REG_DEVICE ; 
 int ATA_TFLAG_DEVICE ; 
 int PDC_LAST_REG ; 

__attribute__((used)) static inline unsigned int pdc_pkt_footer(struct ata_taskfile *tf, u8 *buf,
				  unsigned int i)
{
	if (tf->flags & ATA_TFLAG_DEVICE) {
		buf[i++] = (1 << 5) | ATA_REG_DEVICE;
		buf[i++] = tf->device;
	}

	/* and finally the command itself; also includes end-of-pkt marker */
	buf[i++] = (1 << 5) | PDC_LAST_REG | ATA_REG_CMD;
	buf[i++] = tf->command;

	return i;
}
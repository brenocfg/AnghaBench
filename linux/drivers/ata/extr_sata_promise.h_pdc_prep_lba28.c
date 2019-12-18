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
struct ata_taskfile {int feature; int nsect; int lbal; int lbam; int lbah; } ;

/* Variables and functions */
 int ATA_REG_FEATURE ; 
 int ATA_REG_LBAH ; 
 int ATA_REG_LBAL ; 
 int ATA_REG_LBAM ; 
 int ATA_REG_NSECT ; 

__attribute__((used)) static inline unsigned int pdc_prep_lba28(struct ata_taskfile *tf, u8 *buf, unsigned int i)
{
	/* the "(1 << 5)" should be read "(count << 5)" */

	/* ATA command block registers */
	buf[i++] = (1 << 5) | ATA_REG_FEATURE;
	buf[i++] = tf->feature;

	buf[i++] = (1 << 5) | ATA_REG_NSECT;
	buf[i++] = tf->nsect;

	buf[i++] = (1 << 5) | ATA_REG_LBAL;
	buf[i++] = tf->lbal;

	buf[i++] = (1 << 5) | ATA_REG_LBAM;
	buf[i++] = tf->lbam;

	buf[i++] = (1 << 5) | ATA_REG_LBAH;
	buf[i++] = tf->lbah;

	return i;
}
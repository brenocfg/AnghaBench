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
typedef  int u64 ;
struct ata_taskfile {int device; int lbah; int lbam; int lbal; } ;

/* Variables and functions */

u64 ata_tf_to_lba(const struct ata_taskfile *tf)
{
	u64 sectors = 0;

	sectors |= (tf->device & 0x0f) << 24;
	sectors |= (tf->lbah & 0xff) << 16;
	sectors |= (tf->lbam & 0xff) << 8;
	sectors |= (tf->lbal & 0xff);

	return sectors;
}
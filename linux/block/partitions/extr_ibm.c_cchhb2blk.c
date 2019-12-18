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
struct vtoc_cchhb {int hh; int cc; int b; } ;
struct hd_geometry {int heads; int sectors; } ;
typedef  int sector_t ;
typedef  int __u16 ;

/* Variables and functions */

__attribute__((used)) static sector_t cchhb2blk(struct vtoc_cchhb *ptr, struct hd_geometry *geo)
{
	sector_t cyl;
	__u16 head;

	/* decode cylinder and heads for large volumes */
	cyl = ptr->hh & 0xFFF0;
	cyl <<= 12;
	cyl |= ptr->cc;
	head = ptr->hh & 0x000F;
	return	cyl * geo->heads * geo->sectors +
		head * geo->sectors +
		ptr->b;
}
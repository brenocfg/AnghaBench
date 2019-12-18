#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct edd_packet {int len; int count; int /*<<< orphan*/  lba; void* seg; void* off; } ;
typedef  int /*<<< orphan*/  daddr_t ;
typedef  struct edd_packet* caddr_t ;
struct TYPE_4__ {int /*<<< orphan*/  bd_unit; } ;
typedef  TYPE_1__ bdinfo_t ;
struct TYPE_5__ {int addr; int eax; int /*<<< orphan*/  efl; void* esi; void* ds; int /*<<< orphan*/  edx; int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int BD_WR ; 
 scalar_t__ V86_CY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V86_FLAGS ; 
 void* VTOPOFF (struct edd_packet*) ; 
 void* VTOPSEG (struct edd_packet*) ; 
 TYPE_2__ v86 ; 
 int /*<<< orphan*/  v86int () ; 

__attribute__((used)) static int
bd_edd_io(bdinfo_t *bd, daddr_t dblk, int blks, caddr_t dest,
    int dowrite)
{
	static struct edd_packet packet;

	packet.len = sizeof(struct edd_packet);
	packet.count = blks;
	packet.off = VTOPOFF(dest);
	packet.seg = VTOPSEG(dest);
	packet.lba = dblk;
	v86.ctl = V86_FLAGS;
	v86.addr = 0x13;
	/* Should we Write with verify ?? 0x4302 ? */
	if (dowrite == BD_WR)
		v86.eax = 0x4300;
	else
		v86.eax = 0x4200;
	v86.edx = bd->bd_unit;
	v86.ds = VTOPSEG(&packet);
	v86.esi = VTOPOFF(&packet);
	v86int();
	if (V86_CY(v86.efl))
		return (v86.eax >> 8);
	return (0);
}
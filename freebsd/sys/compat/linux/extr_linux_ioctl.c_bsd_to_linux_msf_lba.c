#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  frame; int /*<<< orphan*/  second; int /*<<< orphan*/  minute; } ;
union msf_lba {TYPE_2__ msf; int /*<<< orphan*/  lba; } ;
struct TYPE_3__ {int /*<<< orphan*/  frame; int /*<<< orphan*/  second; int /*<<< orphan*/  minute; } ;
union linux_cdrom_addr {TYPE_1__ msf; int /*<<< orphan*/  lba; } ;
typedef  scalar_t__ u_char ;

/* Variables and functions */
 scalar_t__ CD_LBA_FORMAT ; 

__attribute__((used)) static void
bsd_to_linux_msf_lba(u_char af, union msf_lba *bp, union linux_cdrom_addr *lp)
{
	if (af == CD_LBA_FORMAT)
		lp->lba = bp->lba;
	else {
		lp->msf.minute = bp->msf.minute;
		lp->msf.second = bp->msf.second;
		lp->msf.frame = bp->msf.frame;
	}
}
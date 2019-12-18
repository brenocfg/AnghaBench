#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_9__ {int* length; int* version; } ;
struct TYPE_12__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; TYPE_1__ h; } ;
struct TYPE_13__ {TYPE_4__ PN; } ;
struct TYPE_14__ {TYPE_5__ rr_entry; } ;
struct ISO_SUSP_ATTRIBUTES {TYPE_6__ attr; } ;
struct TYPE_15__ {TYPE_3__* inode; } ;
typedef  TYPE_7__ fsnode ;
struct TYPE_10__ {int st_rdev; } ;
struct TYPE_11__ {TYPE_2__ st; } ;

/* Variables and functions */
 int /*<<< orphan*/  cd9660_bothendian_dword (int,int /*<<< orphan*/ ) ; 

int
cd9660node_rrip_pn(struct ISO_SUSP_ATTRIBUTES *pn_field, fsnode *fnode)
{
	pn_field->attr.rr_entry.PN.h.length[0] = 20;
	pn_field->attr.rr_entry.PN.h.version[0] = 1;

	if (sizeof (fnode->inode->st.st_rdev) > 4)
		cd9660_bothendian_dword(
		    (uint64_t)fnode->inode->st.st_rdev >> 32,
		    pn_field->attr.rr_entry.PN.high);
	else
		cd9660_bothendian_dword(0, pn_field->attr.rr_entry.PN.high);

	cd9660_bothendian_dword(fnode->inode->st.st_rdev & 0xffffffff,
		pn_field->attr.rr_entry.PN.low);
	return 1;
}
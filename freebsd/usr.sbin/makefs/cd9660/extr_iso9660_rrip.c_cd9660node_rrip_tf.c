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
struct TYPE_11__ {int* length; int* version; } ;
struct TYPE_12__ {int* flags; TYPE_3__ h; scalar_t__ timestamp; } ;
struct TYPE_13__ {TYPE_4__ TF; } ;
struct TYPE_14__ {TYPE_5__ rr_entry; } ;
struct ISO_SUSP_ATTRIBUTES {TYPE_6__ attr; } ;
struct TYPE_15__ {TYPE_2__* inode; } ;
typedef  TYPE_7__ fsnode ;
struct TYPE_9__ {int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; } ;
struct TYPE_10__ {TYPE_1__ st; } ;

/* Variables and functions */
 int TF_ACCESS ; 
 int TF_ATTRIBUTES ; 
 int TF_MODIFY ; 
 int /*<<< orphan*/  cd9660_time_915 (scalar_t__,int /*<<< orphan*/ ) ; 

int
cd9660node_rrip_tf(struct ISO_SUSP_ATTRIBUTES *p, fsnode *_node)
{
	p->attr.rr_entry.TF.flags[0] = TF_MODIFY | TF_ACCESS | TF_ATTRIBUTES;
	p->attr.rr_entry.TF.h.length[0] = 5;
	p->attr.rr_entry.TF.h.version[0] = 1;

	/*
	 * Need to add creation time, backup time,
	 * expiration time, and effective time.
	 */

	cd9660_time_915(p->attr.rr_entry.TF.timestamp,
		_node->inode->st.st_atime);
	p->attr.rr_entry.TF.h.length[0] += 7;

	cd9660_time_915(p->attr.rr_entry.TF.timestamp + 7,
		_node->inode->st.st_mtime);
	p->attr.rr_entry.TF.h.length[0] += 7;

	cd9660_time_915(p->attr.rr_entry.TF.timestamp + 14,
		_node->inode->st.st_ctime);
	p->attr.rr_entry.TF.h.length[0] += 7;
	return 1;
}
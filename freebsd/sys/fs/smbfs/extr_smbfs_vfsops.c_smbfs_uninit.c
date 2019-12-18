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
struct vfsconf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMBVDEBUG (char*) ; 
 int /*<<< orphan*/  smbfs_pbuf_zone ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ ) ; 

int
smbfs_uninit(struct vfsconf *vfsp)
{

	uma_zdestroy(smbfs_pbuf_zone);
	SMBVDEBUG("done.\n");
	return 0;
}
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
 int nswbuf ; 
 int /*<<< orphan*/  pbuf_zsecond_create (char*,int) ; 
 int /*<<< orphan*/  smbfs_pbuf_zone ; 

int
smbfs_init(struct vfsconf *vfsp)
{

	smbfs_pbuf_zone = pbuf_zsecond_create("smbpbuf", nswbuf / 2);
	SMBVDEBUG("done.\n");
	return 0;
}
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
struct vop_ioctl_args {int a_command; int /*<<< orphan*/  a_cred; scalar_t__ a_data; int /*<<< orphan*/  a_vp; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int ENOTTY ; 
#define  FIOSEEKDATA 129 
#define  FIOSEEKHOLE 128 
 int vn_bmap_seekhole (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext2_ioctl(struct vop_ioctl_args *ap)
{

	switch (ap->a_command) {
	case FIOSEEKDATA:
	case FIOSEEKHOLE:
		return (vn_bmap_seekhole(ap->a_vp, ap->a_command,
		    (off_t *)ap->a_data, ap->a_cred));
	default:
		return (ENOTTY);
	}
}
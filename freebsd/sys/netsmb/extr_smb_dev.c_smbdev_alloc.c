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
struct smb_dev {int sd_level; int refcount; int /*<<< orphan*/  sd_flags; struct cdev* dev; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NSMBDEV ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NSMBFL_OPEN ; 
 struct smb_dev* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct smb_dev *
smbdev_alloc(struct cdev *dev)
{
	struct smb_dev *sdp;

	sdp = malloc(sizeof(struct smb_dev), M_NSMBDEV, M_WAITOK | M_ZERO);
	sdp->dev = dev;	
	sdp->sd_level = -1;
	sdp->sd_flags |= NSMBFL_OPEN;
	sdp->refcount = 1;
	return (sdp);	
}
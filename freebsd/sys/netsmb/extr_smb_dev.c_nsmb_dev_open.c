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
struct thread {int dummy; } ;
struct smb_dev {int dummy; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NSMBDEV ; 
 int devfs_set_cdevpriv (struct smb_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct smb_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdp_dtor ; 
 struct smb_dev* smbdev_alloc (struct cdev*) ; 

__attribute__((used)) static int
nsmb_dev_open(struct cdev *dev, int oflags, int devtype, struct thread *td)
{
	struct smb_dev *sdp;
	int error;

	sdp = smbdev_alloc(dev);
	error = devfs_set_cdevpriv(sdp, sdp_dtor);
	if (error) {
		free(sdp, M_NSMBDEV);	
		return (error);
	}
	return (0);
}
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
struct ctl_be_lun {int flags; } ;
struct TYPE_3__ {int /*<<< orphan*/ * cred; } ;
struct TYPE_4__ {TYPE_1__ file; } ;
struct ctl_be_block_lun {int dev_type; TYPE_2__ backend; int /*<<< orphan*/ * vn; struct ctl_be_lun cbe_lun; } ;

/* Variables and functions */
#define  CTL_BE_BLOCK_DEV 130 
#define  CTL_BE_BLOCK_FILE 129 
#define  CTL_BE_BLOCK_NONE 128 
 int CTL_LUN_FLAG_READONLY ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  NOCRED ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  vn_close (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ctl_be_block_close(struct ctl_be_block_lun *be_lun)
{
	struct ctl_be_lun *cbe_lun = &be_lun->cbe_lun;
	int flags;

	if (be_lun->vn) {
		flags = FREAD;
		if ((cbe_lun->flags & CTL_LUN_FLAG_READONLY) == 0)
			flags |= FWRITE;
		(void)vn_close(be_lun->vn, flags, NOCRED, curthread);
		be_lun->vn = NULL;

		switch (be_lun->dev_type) {
		case CTL_BE_BLOCK_DEV:
			break;
		case CTL_BE_BLOCK_FILE:
			if (be_lun->backend.file.cred != NULL) {
				crfree(be_lun->backend.file.cred);
				be_lun->backend.file.cred = NULL;
			}
			break;
		case CTL_BE_BLOCK_NONE:
			break;
		default:
			panic("Unexpected backend type %d", be_lun->dev_type);
			break;
		}
		be_lun->dev_type = CTL_BE_BLOCK_NONE;
	}
	return (0);
}
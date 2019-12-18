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
typedef  int u8 ;
struct TYPE_3__ {int /*<<< orphan*/  lr; } ;
struct TYPE_4__ {TYPE_1__ opal_key; } ;
struct opal_lock_unlock {int l_state; TYPE_2__ session; } ;
struct opal_dev {int /*<<< orphan*/  comid; } ;
typedef  int /*<<< orphan*/  lr_buffer ;

/* Variables and functions */
 int ERANGE ; 
 int OPAL_INVAL_PARAM ; 
#define  OPAL_LK 130 
#define  OPAL_RO 129 
#define  OPAL_RW 128 
 int OPAL_UID_LENGTH ; 
 scalar_t__ build_locking_range (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_opal_cmd (struct opal_dev*) ; 
 int finalize_and_send (struct opal_dev*,int /*<<< orphan*/ ) ; 
 int generic_lr_enable_disable (struct opal_dev*,int*,int,int,int,int) ; 
 int /*<<< orphan*/  parse_and_check_status ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  set_comid (struct opal_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lock_unlock_locking_range_sum(struct opal_dev *dev, void *data)
{
	u8 lr_buffer[OPAL_UID_LENGTH];
	u8 read_locked = 1, write_locked = 1;
	struct opal_lock_unlock *lkul = data;
	int ret;

	clear_opal_cmd(dev);
	set_comid(dev, dev->comid);

	if (build_locking_range(lr_buffer, sizeof(lr_buffer),
				lkul->session.opal_key.lr) < 0)
		return -ERANGE;

	switch (lkul->l_state) {
	case OPAL_RO:
		read_locked = 0;
		write_locked = 1;
		break;
	case OPAL_RW:
		read_locked = 0;
		write_locked = 0;
		break;
	case OPAL_LK:
		/* vars are initialized to locked */
		break;
	default:
		pr_debug("Tried to set an invalid locking state.\n");
		return OPAL_INVAL_PARAM;
	}
	ret = generic_lr_enable_disable(dev, lr_buffer, 1, 1,
					read_locked, write_locked);

	if (ret < 0) {
		pr_debug("Error building SET command.\n");
		return ret;
	}

	return finalize_and_send(dev, parse_and_check_status);
}
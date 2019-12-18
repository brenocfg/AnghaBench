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
struct opal_dev {int dummy; } ;
typedef  int /*<<< orphan*/  lr_buffer ;

/* Variables and functions */
 int ERANGE ; 
 int OPAL_ENDLIST ; 
 int OPAL_ENDNAME ; 
 int OPAL_INVAL_PARAM ; 
#define  OPAL_LK 130 
 int OPAL_READLOCKED ; 
#define  OPAL_RO 129 
#define  OPAL_RW 128 
 size_t OPAL_SET ; 
 int OPAL_STARTLIST ; 
 int OPAL_STARTNAME ; 
 int OPAL_UID_LENGTH ; 
 int OPAL_VALUES ; 
 int OPAL_WRITELOCKED ; 
 int /*<<< orphan*/  add_token_u8 (int*,struct opal_dev*,int) ; 
 scalar_t__ build_locking_range (int*,int,int /*<<< orphan*/ ) ; 
 int cmd_start (struct opal_dev*,int*,int /*<<< orphan*/ ) ; 
 int finalize_and_send (struct opal_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opalmethod ; 
 int /*<<< orphan*/  parse_and_check_status ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int lock_unlock_locking_range(struct opal_dev *dev, void *data)
{
	u8 lr_buffer[OPAL_UID_LENGTH];
	struct opal_lock_unlock *lkul = data;
	u8 read_locked = 1, write_locked = 1;
	int err = 0;

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
		pr_debug("Tried to set an invalid locking state... returning to uland\n");
		return OPAL_INVAL_PARAM;
	}

	err = cmd_start(dev, lr_buffer, opalmethod[OPAL_SET]);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_VALUES);
	add_token_u8(&err, dev, OPAL_STARTLIST);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_READLOCKED);
	add_token_u8(&err, dev, read_locked);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_WRITELOCKED);
	add_token_u8(&err, dev, write_locked);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	add_token_u8(&err, dev, OPAL_ENDLIST);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	if (err) {
		pr_debug("Error building SET command.\n");
		return err;
	}

	return finalize_and_send(dev, parse_and_check_status);
}
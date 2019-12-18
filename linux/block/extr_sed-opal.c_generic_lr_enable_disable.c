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
typedef  int /*<<< orphan*/  u8 ;
struct opal_dev {int dummy; } ;

/* Variables and functions */
 int OPAL_ENDLIST ; 
 int OPAL_ENDNAME ; 
 int OPAL_READLOCKED ; 
 int OPAL_READLOCKENABLED ; 
 size_t OPAL_SET ; 
 int OPAL_STARTLIST ; 
 int OPAL_STARTNAME ; 
 int OPAL_VALUES ; 
 int OPAL_WRITELOCKED ; 
 int OPAL_WRITELOCKENABLED ; 
 int /*<<< orphan*/  add_token_u8 (int*,struct opal_dev*,int) ; 
 int cmd_start (struct opal_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opalmethod ; 

__attribute__((used)) static int generic_lr_enable_disable(struct opal_dev *dev,
				     u8 *uid, bool rle, bool wle,
				     bool rl, bool wl)
{
	int err;

	err = cmd_start(dev, uid, opalmethod[OPAL_SET]);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_VALUES);
	add_token_u8(&err, dev, OPAL_STARTLIST);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_READLOCKENABLED);
	add_token_u8(&err, dev, rle);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_WRITELOCKENABLED);
	add_token_u8(&err, dev, wle);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_READLOCKED);
	add_token_u8(&err, dev, rl);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_WRITELOCKED);
	add_token_u8(&err, dev, wl);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	add_token_u8(&err, dev, OPAL_ENDLIST);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	return err;
}
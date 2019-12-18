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
struct opal_dev {int /*<<< orphan*/  comid; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_CALL ; 
 int /*<<< orphan*/  OPAL_METHOD_LENGTH ; 
 int /*<<< orphan*/  OPAL_STARTLIST ; 
 int /*<<< orphan*/  OPAL_UID_LENGTH ; 
 int /*<<< orphan*/  add_token_bytestring (int*,struct opal_dev*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_token_u8 (int*,struct opal_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_opal_cmd (struct opal_dev*) ; 
 int /*<<< orphan*/  set_comid (struct opal_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmd_start(struct opal_dev *dev, const u8 *uid, const u8 *method)
{
	int err = 0;

	clear_opal_cmd(dev);
	set_comid(dev, dev->comid);

	add_token_u8(&err, dev, OPAL_CALL);
	add_token_bytestring(&err, dev, uid, OPAL_UID_LENGTH);
	add_token_bytestring(&err, dev, method, OPAL_METHOD_LENGTH);

	/*
	 * Every method call is followed by its parameters enclosed within
	 * OPAL_STARTLIST and OPAL_ENDLIST tokens. We automatically open the
	 * parameter list here and close it later in cmd_finalize.
	 */
	add_token_u8(&err, dev, OPAL_STARTLIST);

	return err;
}
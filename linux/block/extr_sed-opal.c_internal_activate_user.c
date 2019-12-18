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
struct opal_session_info {int /*<<< orphan*/  who; } ;
struct opal_dev {int dummy; } ;

/* Variables and functions */
 int OPAL_ENDLIST ; 
 int OPAL_ENDNAME ; 
 size_t OPAL_SET ; 
 int OPAL_STARTLIST ; 
 int OPAL_STARTNAME ; 
 int OPAL_TRUE ; 
 int OPAL_UID_LENGTH ; 
 size_t OPAL_USER1_UID ; 
 int OPAL_VALUES ; 
 int /*<<< orphan*/  add_token_u8 (int*,struct opal_dev*,int) ; 
 int cmd_start (struct opal_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int finalize_and_send (struct opal_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * opalmethod ; 
 int /*<<< orphan*/ * opaluid ; 
 int /*<<< orphan*/  parse_and_check_status ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int internal_activate_user(struct opal_dev *dev, void *data)
{
	struct opal_session_info *session = data;
	u8 uid[OPAL_UID_LENGTH];
	int err;

	memcpy(uid, opaluid[OPAL_USER1_UID], OPAL_UID_LENGTH);
	uid[7] = session->who;

	err = cmd_start(dev, uid, opalmethod[OPAL_SET]);
	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_VALUES);
	add_token_u8(&err, dev, OPAL_STARTLIST);
	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, 5); /* Enabled */
	add_token_u8(&err, dev, OPAL_TRUE);
	add_token_u8(&err, dev, OPAL_ENDNAME);
	add_token_u8(&err, dev, OPAL_ENDLIST);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	if (err) {
		pr_debug("Error building Activate UserN command.\n");
		return err;
	}

	return finalize_and_send(dev, parse_and_check_status);
}
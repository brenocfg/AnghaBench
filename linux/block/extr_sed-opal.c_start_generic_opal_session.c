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
typedef  int /*<<< orphan*/  u32 ;
struct opal_dev {int dummy; } ;
typedef  enum opal_uid { ____Placeholder_opal_uid } opal_uid ;

/* Variables and functions */
 int /*<<< orphan*/  GENERIC_HOST_SESSION_NUM ; 
#define  OPAL_ADMIN1_UID 131 
#define  OPAL_ANYBODY_UID 130 
 int OPAL_ENDNAME ; 
 int OPAL_INVAL_PARAM ; 
#define  OPAL_PSID_UID 129 
#define  OPAL_SID_UID 128 
 size_t OPAL_SMUID_UID ; 
 int OPAL_STARTNAME ; 
 size_t OPAL_STARTSESSION ; 
 int /*<<< orphan*/  OPAL_UID_LENGTH ; 
 int /*<<< orphan*/  add_token_bytestring (int*,struct opal_dev*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_token_u64 (int*,struct opal_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_token_u8 (int*,struct opal_dev*,int) ; 
 int cmd_start (struct opal_dev*,char const*,int /*<<< orphan*/ ) ; 
 int finalize_and_send (struct opal_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opalmethod ; 
 char const** opaluid ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  start_opal_session_cont ; 

__attribute__((used)) static int start_generic_opal_session(struct opal_dev *dev,
				      enum opal_uid auth,
				      enum opal_uid sp_type,
				      const char *key,
				      u8 key_len)
{
	u32 hsn;
	int err;

	if (key == NULL && auth != OPAL_ANYBODY_UID)
		return OPAL_INVAL_PARAM;

	hsn = GENERIC_HOST_SESSION_NUM;
	err = cmd_start(dev, opaluid[OPAL_SMUID_UID],
			opalmethod[OPAL_STARTSESSION]);

	add_token_u64(&err, dev, hsn);
	add_token_bytestring(&err, dev, opaluid[sp_type], OPAL_UID_LENGTH);
	add_token_u8(&err, dev, 1);

	switch (auth) {
	case OPAL_ANYBODY_UID:
		break;
	case OPAL_ADMIN1_UID:
	case OPAL_SID_UID:
	case OPAL_PSID_UID:
		add_token_u8(&err, dev, OPAL_STARTNAME);
		add_token_u8(&err, dev, 0); /* HostChallenge */
		add_token_bytestring(&err, dev, key, key_len);
		add_token_u8(&err, dev, OPAL_ENDNAME);
		add_token_u8(&err, dev, OPAL_STARTNAME);
		add_token_u8(&err, dev, 3); /* HostSignAuth */
		add_token_bytestring(&err, dev, opaluid[auth],
				     OPAL_UID_LENGTH);
		add_token_u8(&err, dev, OPAL_ENDNAME);
		break;
	default:
		pr_debug("Cannot start Admin SP session with auth %d\n", auth);
		return OPAL_INVAL_PARAM;
	}

	if (err) {
		pr_debug("Error building start adminsp session command.\n");
		return err;
	}

	return finalize_and_send(dev, start_opal_session_cont);
}
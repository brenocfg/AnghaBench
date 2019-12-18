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
struct opal_dev {int /*<<< orphan*/  comid; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_ENDOFSESSION ; 
 int /*<<< orphan*/  add_token_u8 (int*,struct opal_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_opal_cmd (struct opal_dev*) ; 
 int /*<<< orphan*/  end_session_cont ; 
 int finalize_and_send (struct opal_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_comid (struct opal_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int end_opal_session(struct opal_dev *dev, void *data)
{
	int err = 0;

	clear_opal_cmd(dev);
	set_comid(dev, dev->comid);
	add_token_u8(&err, dev, OPAL_ENDOFSESSION);

	if (err < 0)
		return err;

	return finalize_and_send(dev, end_session_cont);
}
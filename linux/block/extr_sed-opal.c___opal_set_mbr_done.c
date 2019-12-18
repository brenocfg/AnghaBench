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
struct opal_key {int dummy; } ;
typedef  struct opal_key u8 ;
struct opal_step {int /*<<< orphan*/  member_0; struct opal_key* member_1; } ;
struct opal_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct opal_step const*) ; 
 struct opal_key OPAL_TRUE ; 
 int /*<<< orphan*/  end_opal_session ; 
 int execute_steps (struct opal_dev*,struct opal_step const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mbr_done ; 
 int /*<<< orphan*/  start_admin1LSP_opal_session ; 

__attribute__((used)) static int __opal_set_mbr_done(struct opal_dev *dev, struct opal_key *key)
{
	u8 mbr_done_tf = OPAL_TRUE;
	const struct opal_step mbrdone_step[] = {
		{ start_admin1LSP_opal_session, key },
		{ set_mbr_done, &mbr_done_tf },
		{ end_opal_session, }
	};

	return execute_steps(dev, mbrdone_step, ARRAY_SIZE(mbrdone_step));
}
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
struct target {int dummy; } ;
struct iscsi_session_modify {unsigned int ism_session_id; int /*<<< orphan*/  ism_conf; } ;
typedef  int /*<<< orphan*/  ism ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSISMODIFY ; 
 int /*<<< orphan*/  conf_from_target (int /*<<< orphan*/ *,struct target const*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct iscsi_session_modify*) ; 
 int /*<<< orphan*/  memset (struct iscsi_session_modify*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xo_warn (char*) ; 

__attribute__((used)) static int
kernel_modify(int iscsi_fd, unsigned int session_id, const struct target *targ)
{
	struct iscsi_session_modify ism;
	int error;

	memset(&ism, 0, sizeof(ism));
	ism.ism_session_id = session_id;
	conf_from_target(&ism.ism_conf, targ);
	error = ioctl(iscsi_fd, ISCSISMODIFY, &ism);
	if (error != 0)
		xo_warn("ISCSISMODIFY");
	return (error);
}
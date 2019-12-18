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
struct iscsi_session_add {int /*<<< orphan*/  isa_conf; } ;
typedef  int /*<<< orphan*/  isa ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSISADD ; 
 int /*<<< orphan*/  conf_from_target (int /*<<< orphan*/ *,struct target const*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct iscsi_session_add*) ; 
 int /*<<< orphan*/  memset (struct iscsi_session_add*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xo_warn (char*) ; 

__attribute__((used)) static int
kernel_add(int iscsi_fd, const struct target *targ)
{
	struct iscsi_session_add isa;
	int error;

	memset(&isa, 0, sizeof(isa));
	conf_from_target(&isa.isa_conf, targ);
	error = ioctl(iscsi_fd, ISCSISADD, &isa);
	if (error != 0)
		xo_warn("ISCSISADD");
	return (error);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ isc_discovery; int /*<<< orphan*/  isc_target; } ;
struct iscsi_session_add {TYPE_1__ isa_conf; } ;
struct connection {int /*<<< orphan*/  conn_iscsi_fd; int /*<<< orphan*/  conn_conf; } ;
typedef  int /*<<< orphan*/  isa ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSISADD ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iscsi_session_add*) ; 
 int /*<<< orphan*/  log_warn (char*,char const*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct iscsi_session_add*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
kernel_add(const struct connection *conn, const char *target)
{
	struct iscsi_session_add isa;
	int error;

	memset(&isa, 0, sizeof(isa));
	memcpy(&isa.isa_conf, &conn->conn_conf, sizeof(isa.isa_conf));
	strlcpy(isa.isa_conf.isc_target, target,
	    sizeof(isa.isa_conf.isc_target));
	isa.isa_conf.isc_discovery = 0;
	error = ioctl(conn->conn_iscsi_fd, ISCSISADD, &isa);
	if (error != 0)
		log_warn("failed to add %s: ISCSISADD", target);
}
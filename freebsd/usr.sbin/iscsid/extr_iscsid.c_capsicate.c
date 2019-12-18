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
struct connection {int /*<<< orphan*/  conn_iscsi_fd; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IOCTL ; 
 unsigned long const ISCSIDCONNECT ; 
 unsigned long const ISCSIDFAIL ; 
 unsigned long const ISCSIDHANDOFF ; 
 unsigned long const ISCSIDRECEIVE ; 
 unsigned long const ISCSIDSEND ; 
 unsigned long const ISCSISADD ; 
 unsigned long const ISCSISMODIFY ; 
 unsigned long const ISCSISREMOVE ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cap_sandboxed () ; 
 scalar_t__ caph_enter () ; 
 scalar_t__ caph_ioctls_limit (int /*<<< orphan*/ ,unsigned long const*,int /*<<< orphan*/ ) ; 
 scalar_t__ caph_rights_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debugx (char*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  log_warnx (char*) ; 
 int /*<<< orphan*/  nitems (unsigned long const*) ; 

__attribute__((used)) static void
capsicate(struct connection *conn)
{
	cap_rights_t rights;
#ifdef ICL_KERNEL_PROXY
	const unsigned long cmds[] = { ISCSIDCONNECT, ISCSIDSEND, ISCSIDRECEIVE,
	    ISCSIDHANDOFF, ISCSIDFAIL, ISCSISADD, ISCSISREMOVE, ISCSISMODIFY };
#else
	const unsigned long cmds[] = { ISCSIDHANDOFF, ISCSIDFAIL, ISCSISADD,
	    ISCSISREMOVE, ISCSISMODIFY };
#endif

	cap_rights_init(&rights, CAP_IOCTL);
	if (caph_rights_limit(conn->conn_iscsi_fd, &rights) < 0)
		log_err(1, "cap_rights_limit");

	if (caph_ioctls_limit(conn->conn_iscsi_fd, cmds, nitems(cmds)) < 0)
		log_err(1, "cap_ioctls_limit");

	if (caph_enter() != 0)
		log_err(1, "cap_enter");

	if (cap_sandboxed())
		log_debugx("Capsicum capability mode enabled");
	else
		log_warnx("Capsicum capability mode not supported");
}
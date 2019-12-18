#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
struct sockcred {scalar_t__ sc_uid; scalar_t__ sc_euid; scalar_t__ sc_gid; scalar_t__ sc_egid; scalar_t__ sc_ngroups; int /*<<< orphan*/  sc_groups; } ;
struct cmsghdr {int dummy; } ;
struct TYPE_3__ {scalar_t__ gid_num; scalar_t__ uid; scalar_t__ euid; scalar_t__ gid; scalar_t__ egid; } ;
struct TYPE_4__ {TYPE_1__ proc_cred; } ;

/* Variables and functions */
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 int /*<<< orphan*/  SCM_CREDS ; 
 int /*<<< orphan*/  SOCKCREDSIZE (scalar_t__) ; 
 TYPE_2__ uc_cfg ; 
 scalar_t__ uc_check_cmsghdr (struct cmsghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uc_check_groups (char*,int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  uc_dbgmsg (char*,scalar_t__) ; 
 int /*<<< orphan*/  uc_logmsgx (char*,...) ; 

int
uc_check_scm_creds_sockcred(struct cmsghdr *cmsghdr)
{
	const struct sockcred *sc;
	int rc;

	if (uc_check_cmsghdr(cmsghdr, SCM_CREDS,
	    SOCKCREDSIZE(uc_cfg.proc_cred.gid_num)) < 0)
		return (-1);

	sc = (struct sockcred *)CMSG_DATA(cmsghdr);

	rc = 0;

	uc_dbgmsg("sockcred.sc_uid %lu", (u_long)sc->sc_uid);
	uc_dbgmsg("sockcred.sc_euid %lu", (u_long)sc->sc_euid);
	uc_dbgmsg("sockcred.sc_gid %lu", (u_long)sc->sc_gid);
	uc_dbgmsg("sockcred.sc_egid %lu", (u_long)sc->sc_egid);
	uc_dbgmsg("sockcred.sc_ngroups %d", sc->sc_ngroups);

	if (sc->sc_uid != uc_cfg.proc_cred.uid) {
		uc_logmsgx("sockcred.sc_uid %lu != %lu",
		    (u_long)sc->sc_uid, (u_long)uc_cfg.proc_cred.uid);
		rc = -1;
	}
	if (sc->sc_euid != uc_cfg.proc_cred.euid) {
		uc_logmsgx("sockcred.sc_euid %lu != %lu",
		    (u_long)sc->sc_euid, (u_long)uc_cfg.proc_cred.euid);
		rc = -1;
	}
	if (sc->sc_gid != uc_cfg.proc_cred.gid) {
		uc_logmsgx("sockcred.sc_gid %lu != %lu",
		    (u_long)sc->sc_gid, (u_long)uc_cfg.proc_cred.gid);
		rc = -1;
	}
	if (sc->sc_egid != uc_cfg.proc_cred.egid) {
		uc_logmsgx("sockcred.sc_egid %lu != %lu",
		    (u_long)sc->sc_egid, (u_long)uc_cfg.proc_cred.egid);
		rc = -1;
	}
	if (sc->sc_ngroups == 0) {
		uc_logmsgx("sockcred.sc_ngroups == 0");
		rc = -1;
	}
	if (sc->sc_ngroups < 0) {
		uc_logmsgx("sockcred.sc_ngroups %d < 0",
		    sc->sc_ngroups);
		rc = -1;
	}
	if (sc->sc_ngroups != uc_cfg.proc_cred.gid_num) {
		uc_logmsgx("sockcred.sc_ngroups %d != %u",
		    sc->sc_ngroups, uc_cfg.proc_cred.gid_num);
		rc = -1;
	}
	if (uc_check_groups("sockcred.sc_groups", sc->sc_groups,
	    "sockcred.sc_ngroups", sc->sc_ngroups, true) < 0)
		rc = -1;
	return (rc);
}
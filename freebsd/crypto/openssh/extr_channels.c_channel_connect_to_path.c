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
typedef  size_t u_int ;
struct permission_set {size_t all_permitted; size_t num_permitted_user; size_t num_permitted_admin; struct permission* permitted_admin; struct permission* permitted_user; } ;
struct ssh_channels {struct permission_set local_perms; } ;
struct ssh {struct ssh_channels* chanctxt; } ;
struct permission {int dummy; } ;
typedef  int /*<<< orphan*/  Channel ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_STREAMLOCAL ; 
 int /*<<< orphan*/ * connect_to (struct ssh*,char const*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  logit (char*,char const*) ; 
 scalar_t__ open_match (struct permission*,char const*,int /*<<< orphan*/ ) ; 

Channel *
channel_connect_to_path(struct ssh *ssh, const char *path,
    char *ctype, char *rname)
{
	struct ssh_channels *sc = ssh->chanctxt;
	struct permission_set *pset = &sc->local_perms;
	u_int i, permit, permit_adm = 1;
	struct permission *perm;

	permit = pset->all_permitted;
	if (!permit) {
		for (i = 0; i < pset->num_permitted_user; i++) {
			perm = &pset->permitted_user[i];
			if (open_match(perm, path, PORT_STREAMLOCAL)) {
				permit = 1;
				break;
			}
		}
	}

	if (pset->num_permitted_admin > 0) {
		permit_adm = 0;
		for (i = 0; i < pset->num_permitted_admin; i++) {
			perm = &pset->permitted_admin[i];
			if (open_match(perm, path, PORT_STREAMLOCAL)) {
				permit_adm = 1;
				break;
			}
		}
	}

	if (!permit || !permit_adm) {
		logit("Received request to connect to path %.100s, "
		    "but the request was denied.", path);
		return NULL;
	}
	return connect_to(ssh, path, PORT_STREAMLOCAL, ctype, rname);
}
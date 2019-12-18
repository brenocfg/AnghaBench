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
struct ssh_channels {struct permission_set remote_perms; } ;
struct ssh {struct ssh_channels* chanctxt; } ;
struct permission {int dummy; } ;
struct Forward {int dummy; } ;

/* Variables and functions */
 scalar_t__ remote_open_match (struct permission*,struct Forward*) ; 

__attribute__((used)) static int
check_rfwd_permission(struct ssh *ssh, struct Forward *fwd)
{
	struct ssh_channels *sc = ssh->chanctxt;
	struct permission_set *pset = &sc->remote_perms;
	u_int i, permit, permit_adm = 1;
	struct permission *perm;

	/* XXX apply GatewayPorts override before checking? */

	permit = pset->all_permitted;
	if (!permit) {
		for (i = 0; i < pset->num_permitted_user; i++) {
			perm = &pset->permitted_user[i];
			if (remote_open_match(perm, fwd)) {
				permit = 1;
				break;
			}
		}
	}

	if (pset->num_permitted_admin > 0) {
		permit_adm = 0;
		for (i = 0; i < pset->num_permitted_admin; i++) {
			perm = &pset->permitted_admin[i];
			if (remote_open_match(perm, fwd)) {
				permit_adm = 1;
				break;
			}
		}
	}

	return permit && permit_adm;
}
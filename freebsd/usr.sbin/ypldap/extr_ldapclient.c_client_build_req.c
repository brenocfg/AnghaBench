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
struct TYPE_2__ {void* ik_uid; void* ik_gid; } ;
struct idm_req {int /*<<< orphan*/  ir_line; TYPE_1__ ir_key; } ;
struct idm {int idm_flags; char** idm_attrs; int idm_list; } ;
struct aldap_message {int dummy; } ;

/* Variables and functions */
 int ATTR_GR_GID ; 
 int ATTR_UID ; 
 int F_FIXED_ATTR (int) ; 
 int F_LIST (int) ; 
 int /*<<< orphan*/  GID_MAX ; 
 int /*<<< orphan*/  UID_MAX ; 
 int /*<<< orphan*/  aldap_free_attr (char**) ; 
 int aldap_match_attr (struct aldap_message*,char*,char***) ; 
 int /*<<< orphan*/  memset (struct idm_req*,int /*<<< orphan*/ ,int) ; 
 int strlcat (int /*<<< orphan*/ ,char*,int) ; 
 void* strtonum (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
client_build_req(struct idm *idm, struct idm_req *ir, struct aldap_message *m,
    int min_attr, int max_attr)
{
	char	**ldap_attrs;
	int	 i, k;

	memset(ir, 0, sizeof(*ir));
	for (i = min_attr; i < max_attr; i++) {
		if (idm->idm_flags & F_FIXED_ATTR(i)) {
			if (strlcat(ir->ir_line, idm->idm_attrs[i],
			    sizeof(ir->ir_line)) >= sizeof(ir->ir_line))
				/*
				 * entry yields a line > 1024, trash it.
				 */
				return (-1);

			if (i == ATTR_UID) {
				ir->ir_key.ik_uid = strtonum(
				    idm->idm_attrs[i], 0,
				    UID_MAX, NULL);
			} else if (i == ATTR_GR_GID) {
				ir->ir_key.ik_gid = strtonum(
				    idm->idm_attrs[i], 0,
				    GID_MAX, NULL);
			}
		} else if (idm->idm_list & F_LIST(i)) {
			aldap_match_attr(m, idm->idm_attrs[i], &ldap_attrs);
			for (k = 0; k >= 0 && ldap_attrs && ldap_attrs[k] != NULL; k++) {
				/* XXX: Fail when attributes have illegal characters e.g. ',' */
				if (strlcat(ir->ir_line, ldap_attrs[k],
				    sizeof(ir->ir_line)) >= sizeof(ir->ir_line))
					continue;
				if (ldap_attrs[k+1] != NULL)
					if (strlcat(ir->ir_line, ",",
						    sizeof(ir->ir_line))
					    >= sizeof(ir->ir_line)) {
						aldap_free_attr(ldap_attrs);
						return (-1);
					}
			}
			aldap_free_attr(ldap_attrs);
		} else {
			if (aldap_match_attr(m, idm->idm_attrs[i], &ldap_attrs) == -1)
				return (-1);
			if (strlcat(ir->ir_line, ldap_attrs[0],
			    sizeof(ir->ir_line)) >= sizeof(ir->ir_line)) {
				aldap_free_attr(ldap_attrs);
				return (-1);
			}
			if (i == ATTR_UID) {
				ir->ir_key.ik_uid = strtonum(
				    ldap_attrs[0], 0, UID_MAX, NULL);
			} else if (i == ATTR_GR_GID) {
				ir->ir_key.ik_uid = strtonum(
				    ldap_attrs[0], 0, GID_MAX, NULL);
			}
			aldap_free_attr(ldap_attrs);
		}

		if (i + 1 != max_attr)
			if (strlcat(ir->ir_line, ":",
			    sizeof(ir->ir_line)) >= sizeof(ir->ir_line))
				return (-1);
	}

	return (0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ type; } ;
typedef  TYPE_1__ ucl_object_t ;
typedef  int /*<<< orphan*/ * ucl_object_iter_t ;
struct target {int /*<<< orphan*/  t_name; TYPE_5__* t_auth_group; int /*<<< orphan*/  t_alias; } ;
struct pport {int /*<<< orphan*/  pp_ports; } ;
struct port {int dummy; } ;
struct auth_portal {int dummy; } ;
struct auth_name {int dummy; } ;
struct TYPE_18__ {struct target* ag_target; int /*<<< orphan*/ * ag_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ UCL_ARRAY ; 
 scalar_t__ UCL_OBJECT ; 
 scalar_t__ UCL_STRING ; 
 TYPE_5__* auth_group_find (int /*<<< orphan*/ ,char*) ; 
 void* auth_group_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int auth_group_set_type (TYPE_5__*,char*) ; 
 struct auth_name* auth_name_new (TYPE_5__*,char*) ; 
 struct auth_portal* auth_portal_new (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  conf ; 
 int /*<<< orphan*/  log_warnx (char*,char const*,...) ; 
 struct port* port_new_ioctl (int /*<<< orphan*/ ,struct target*,int,int) ; 
 struct port* port_new_pp (int /*<<< orphan*/ ,struct target*,struct pport*) ; 
 struct pport* pport_find (int /*<<< orphan*/ ,char const*) ; 
 int sscanf (char const*,char*,int*,int*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 struct target* target_new (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ target_set_redirection (struct target*,char*) ; 
 TYPE_1__* ucl_iterate_object (TYPE_1__ const*,int /*<<< orphan*/ **,int) ; 
 char* ucl_object_key (TYPE_1__ const*) ; 
 char* ucl_object_tostring (TYPE_1__ const*) ; 
 scalar_t__ uclparse_chap (TYPE_5__*,TYPE_1__ const*) ; 
 scalar_t__ uclparse_chap_mutual (TYPE_5__*,TYPE_1__ const*) ; 
 scalar_t__ uclparse_target_lun (struct target*,TYPE_1__ const*) ; 
 scalar_t__ uclparse_target_portal_group (struct target*,TYPE_1__ const*) ; 

__attribute__((used)) static int
uclparse_target(const char *name, const ucl_object_t *top)
{
	struct target *target;
	ucl_object_iter_t it = NULL, it2 = NULL;
	const ucl_object_t *obj = NULL, *tmp = NULL;
	const char *key;

	target = target_new(conf, name);
	if (target == NULL)
		return (1);

	while ((obj = ucl_iterate_object(top, &it, true))) {
		key = ucl_object_key(obj);

		if (!strcmp(key, "alias")) {
			if (obj->type != UCL_STRING) {
				log_warnx("\"alias\" property of target "
				    "\"%s\" is not a string", target->t_name);
				return (1);
			}

			target->t_alias = strdup(ucl_object_tostring(obj));
		}

		if (!strcmp(key, "auth-group")) {
			if (target->t_auth_group != NULL) {
				if (target->t_auth_group->ag_name != NULL)
					log_warnx("auth-group for target \"%s\" "
					    "specified more than once",
					    target->t_name);
				else
					log_warnx("cannot use both auth-group "
					    "and explicit authorisations for "
					    "target \"%s\"", target->t_name);
				return (1);
			}
			target->t_auth_group = auth_group_find(conf,
			    ucl_object_tostring(obj));
			if (target->t_auth_group == NULL) {
				log_warnx("unknown auth-group \"%s\" for target "
				    "\"%s\"", ucl_object_tostring(obj),
				    target->t_name);
				return (1);
			}
		}

		if (!strcmp(key, "auth-type")) {
			int error;

			if (target->t_auth_group != NULL) {
				if (target->t_auth_group->ag_name != NULL) {
					log_warnx("cannot use both auth-group and "
					    "auth-type for target \"%s\"",
					    target->t_name);
					return (1);
				}
			} else {
				target->t_auth_group = auth_group_new(conf, NULL);
				if (target->t_auth_group == NULL)
					return (1);
	
				target->t_auth_group->ag_target = target;
			}
			error = auth_group_set_type(target->t_auth_group,
			    ucl_object_tostring(obj));
			if (error != 0)
				return (1);
		}

		if (!strcmp(key, "chap")) {
			if (uclparse_chap(target->t_auth_group, obj) != 0)
				return (1);
		}

		if (!strcmp(key, "chap-mutual")) {
			if (uclparse_chap_mutual(target->t_auth_group, obj) != 0)
				return (1);
		}

		if (!strcmp(key, "initiator-name")) {
			const struct auth_name *an;

			if (target->t_auth_group != NULL) {
				if (target->t_auth_group->ag_name != NULL) {
					log_warnx("cannot use both auth-group and "
					    "initiator-name for target \"%s\"",
					    target->t_name);
					return (1);
				}
			} else {
				target->t_auth_group = auth_group_new(conf, NULL);
				if (target->t_auth_group == NULL)
					return (1);

				target->t_auth_group->ag_target = target;
			}
			an = auth_name_new(target->t_auth_group,
			    ucl_object_tostring(obj));
			if (an == NULL)
				return (1);
		}

		if (!strcmp(key, "initiator-portal")) {
			const struct auth_portal *ap;

			if (target->t_auth_group != NULL) {
				if (target->t_auth_group->ag_name != NULL) {
					log_warnx("cannot use both auth-group and "
					    "initiator-portal for target \"%s\"",
					    target->t_name);
					return (1);
				}
			} else {
				target->t_auth_group = auth_group_new(conf, NULL);
				if (target->t_auth_group == NULL)
					return (1);

				target->t_auth_group->ag_target = target;
			}
			ap = auth_portal_new(target->t_auth_group,
			    ucl_object_tostring(obj));
			if (ap == NULL)
				return (1);
		}

		if (!strcmp(key, "portal-group")) {
			if (obj->type == UCL_OBJECT) {
				if (uclparse_target_portal_group(target, obj) != 0)
					return (1);
			}

			if (obj->type == UCL_ARRAY) {
				while ((tmp = ucl_iterate_object(obj, &it2,
				    true))) {
					if (uclparse_target_portal_group(target,
					    tmp) != 0)
						return (1);
				}
			}
		}

		if (!strcmp(key, "port")) {
			struct pport *pp;
			struct port *tp;
			const char *value = ucl_object_tostring(obj);
			int ret, i_pp, i_vp = 0;

			ret = sscanf(value, "ioctl/%d/%d", &i_pp, &i_vp);
			if (ret > 0) {
				tp = port_new_ioctl(conf, target, i_pp, i_vp);
				if (tp == NULL) {
					log_warnx("can't create new ioctl port "
					    "for target \"%s\"", target->t_name);
					return (1);
				}

				return (0);
			}

			pp = pport_find(conf, value);
			if (pp == NULL) {
				log_warnx("unknown port \"%s\" for target \"%s\"",
				    value, target->t_name);
				return (1);
			}
			if (!TAILQ_EMPTY(&pp->pp_ports)) {
				log_warnx("can't link port \"%s\" to target \"%s\", "
				    "port already linked to some target",
				    value, target->t_name);
				return (1);
			}
			tp = port_new_pp(conf, target, pp);
			if (tp == NULL) {
				log_warnx("can't link port \"%s\" to target \"%s\"",
				    value, target->t_name);
				return (1);
			}
		}

		if (!strcmp(key, "redirect")) {
			if (obj->type != UCL_STRING) {
				log_warnx("\"redirect\" property of target "
				    "\"%s\" is not a string", target->t_name);
				return (1);
			}

			if (target_set_redirection(target,
			    ucl_object_tostring(obj)) != 0)
				return (1);
		}

		if (!strcmp(key, "lun")) {
			while ((tmp = ucl_iterate_object(obj, &it2, true))) {
				if (uclparse_target_lun(target, tmp) != 0)
					return (1);
			}
		}
	}

	return (0);
}
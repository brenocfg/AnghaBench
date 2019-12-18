#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; } ;
typedef  TYPE_1__ ucl_object_t ;
struct target {int /*<<< orphan*/  t_name; } ;
struct portal_group {int dummy; } ;
struct port {struct auth_group* p_auth_group; } ;
struct auth_group {int dummy; } ;

/* Variables and functions */
 scalar_t__ UCL_STRING ; 
 struct auth_group* auth_group_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conf ; 
 int /*<<< orphan*/  log_warnx (char*,int /*<<< orphan*/ ,...) ; 
 struct port* port_new (int /*<<< orphan*/ ,struct target*,struct portal_group*) ; 
 struct portal_group* portal_group_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ucl_object_find_key (TYPE_1__ const*,char*) ; 
 int /*<<< orphan*/  ucl_object_tostring (TYPE_1__ const*) ; 

__attribute__((used)) static int
uclparse_target_portal_group(struct target *target, const ucl_object_t *obj)
{
	struct portal_group *tpg;
	struct auth_group *tag = NULL;
	struct port *tp;
	const ucl_object_t *portal_group, *auth_group;

	portal_group = ucl_object_find_key(obj, "name");
	if (!portal_group || portal_group->type != UCL_STRING) {
		log_warnx("portal-group section in target \"%s\" is missing "
		    "\"name\" string key", target->t_name);
		return (1);
	}

	auth_group = ucl_object_find_key(obj, "auth-group-name");
	if (auth_group && auth_group->type != UCL_STRING) {
		log_warnx("portal-group section in target \"%s\" is missing "
		    "\"auth-group-name\" string key", target->t_name);
		return (1);
	}


	tpg = portal_group_find(conf, ucl_object_tostring(portal_group));
	if (tpg == NULL) {
		log_warnx("unknown portal-group \"%s\" for target "
		    "\"%s\"", ucl_object_tostring(portal_group), target->t_name);
		return (1);
	}

	if (auth_group) {
		tag = auth_group_find(conf, ucl_object_tostring(auth_group));
		if (tag == NULL) {
			log_warnx("unknown auth-group \"%s\" for target "
			    "\"%s\"", ucl_object_tostring(auth_group),
			    target->t_name);
			return (1);
		}
	}

	tp = port_new(conf, target, tpg);
	if (tp == NULL) {
		log_warnx("can't link portal-group \"%s\" to target "
		    "\"%s\"", ucl_object_tostring(portal_group), target->t_name);
		return (1);
	}
	tp->p_auth_group = tag;

	return (0);
}
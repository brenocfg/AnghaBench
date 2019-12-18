#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ type; } ;
typedef  TYPE_1__ ucl_object_t ;
typedef  int /*<<< orphan*/ * ucl_object_iter_t ;
struct portal_group {int /*<<< orphan*/  pg_options; int /*<<< orphan*/  pg_name; int /*<<< orphan*/ * pg_discovery_auth_group; } ;
struct TYPE_13__ {int conf_default_pg_defined; } ;

/* Variables and functions */
 scalar_t__ UCL_ARRAY ; 
 scalar_t__ UCL_OBJECT ; 
 scalar_t__ UCL_STRING ; 
 int /*<<< orphan*/ * auth_group_find (TYPE_8__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* conf ; 
 int /*<<< orphan*/  log_warnx (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  option_new (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ portal_group_add_listen (struct portal_group*,int /*<<< orphan*/ ,int) ; 
 struct portal_group* portal_group_find (TYPE_8__*,char const*) ; 
 struct portal_group* portal_group_new (TYPE_8__*,char const*) ; 
 scalar_t__ portal_group_set_filter (struct portal_group*,int /*<<< orphan*/ ) ; 
 scalar_t__ portal_group_set_redirection (struct portal_group*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 TYPE_1__* ucl_iterate_object (TYPE_1__ const*,int /*<<< orphan*/ **,int) ; 
 char* ucl_object_key (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ucl_object_tostring (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ucl_object_tostring_forced (TYPE_1__ const*) ; 

__attribute__((used)) static int
uclparse_portal_group(const char *name, const ucl_object_t *top)
{
	struct portal_group *portal_group;
	ucl_object_iter_t it = NULL, it2 = NULL;
	const ucl_object_t *obj = NULL, *tmp = NULL;
	const char *key;

	if (strcmp(name, "default") == 0 &&
	    conf->conf_default_pg_defined == false) {
		portal_group = portal_group_find(conf, name);
		conf->conf_default_pg_defined = true;
	} else {
		portal_group = portal_group_new(conf, name);
	}

	if (portal_group == NULL)
		return (1);

	while ((obj = ucl_iterate_object(top, &it, true))) {
		key = ucl_object_key(obj);

		if (!strcmp(key, "discovery-auth-group")) {
			portal_group->pg_discovery_auth_group =
			    auth_group_find(conf, ucl_object_tostring(obj));
			if (portal_group->pg_discovery_auth_group == NULL) {
				log_warnx("unknown discovery-auth-group \"%s\" "
				    "for portal-group \"%s\"",
				    ucl_object_tostring(obj),
				    portal_group->pg_name);
				return (1);
			}
		}

		if (!strcmp(key, "discovery-filter")) {
			if (obj->type != UCL_STRING) {
				log_warnx("\"discovery-filter\" property of "
				    "portal-group \"%s\" is not a string",
				    portal_group->pg_name);
				return (1);
			}

			if (portal_group_set_filter(portal_group,
			    ucl_object_tostring(obj)) != 0)
				return (1);
		}

		if (!strcmp(key, "listen")) {
			if (obj->type == UCL_STRING) {
				if (portal_group_add_listen(portal_group,
				    ucl_object_tostring(obj), false) != 0)
					return (1);
			} else if (obj->type == UCL_ARRAY) {
				while ((tmp = ucl_iterate_object(obj, &it2,
				    true))) {
					if (portal_group_add_listen(
					    portal_group, 
					    ucl_object_tostring(tmp),
					    false) != 0)
						return (1);
				}
			} else {
				log_warnx("\"listen\" property of "
				    "portal-group \"%s\" is not a string",
				    portal_group->pg_name);
				return (1);
			}
		}

		if (!strcmp(key, "listen-iser")) {
			if (obj->type == UCL_STRING) {
				if (portal_group_add_listen(portal_group,
				    ucl_object_tostring(obj), true) != 0)
					return (1);
			} else if (obj->type == UCL_ARRAY) {
				while ((tmp = ucl_iterate_object(obj, &it2,
				    true))) {
					if (portal_group_add_listen(
					    portal_group,
					    ucl_object_tostring(tmp),
					    true) != 0)
						return (1);
				}
			} else {
				log_warnx("\"listen\" property of "
				    "portal-group \"%s\" is not a string",
				    portal_group->pg_name);
				return (1);
			}
		}

		if (!strcmp(key, "redirect")) {
			if (obj->type != UCL_STRING) {
				log_warnx("\"listen\" property of "
				    "portal-group \"%s\" is not a string",
				    portal_group->pg_name);
				return (1);
			}

			if (portal_group_set_redirection(portal_group,
			    ucl_object_tostring(obj)) != 0)
				return (1);
		}

		if (!strcmp(key, "options")) {
			if (obj->type != UCL_OBJECT) {
				log_warnx("\"options\" property of portal group "
				    "\"%s\" is not an object", portal_group->pg_name);
				return (1);
			}

			while ((tmp = ucl_iterate_object(obj, &it2,
			    true))) {
				option_new(&portal_group->pg_options,
				    ucl_object_key(tmp),
				    ucl_object_tostring_forced(tmp));
			}
		}
	}	

	return (0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ type; } ;
typedef  TYPE_1__ ucl_object_t ;
typedef  int /*<<< orphan*/ * ucl_object_iter_t ;
struct TYPE_14__ {void* conf_timeout; int /*<<< orphan*/  conf_pidfile_path; void* conf_maxproc; void* conf_debug; } ;

/* Variables and functions */
 scalar_t__ UCL_ARRAY ; 
 scalar_t__ UCL_INT ; 
 scalar_t__ UCL_OBJECT ; 
 scalar_t__ UCL_STRING ; 
 TYPE_12__* conf ; 
 int isns_new (TYPE_12__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_warnx (char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 TYPE_1__* ucl_iterate_object (TYPE_1__ const*,int /*<<< orphan*/ **,int) ; 
 char* ucl_object_key (TYPE_1__ const*) ; 
 void* ucl_object_toint (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ucl_object_tostring (TYPE_1__ const*) ; 
 int /*<<< orphan*/  uclparse_auth_group (char*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  uclparse_lun (char*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  uclparse_portal_group (char*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  uclparse_target (char*,TYPE_1__ const*) ; 

__attribute__((used)) static int
uclparse_toplevel(const ucl_object_t *top)
{
	ucl_object_iter_t it = NULL, iter = NULL;
	const ucl_object_t *obj = NULL, *child = NULL;
	int err = 0;

	/* Pass 1 - everything except targets */
	while ((obj = ucl_iterate_object(top, &it, true))) {
		const char *key = ucl_object_key(obj);

		if (!strcmp(key, "debug")) {
			if (obj->type == UCL_INT)
				conf->conf_debug = ucl_object_toint(obj);
			else {
				log_warnx("\"debug\" property value is not integer");
				return (1);
			}
		}

		if (!strcmp(key, "timeout")) {
			if (obj->type == UCL_INT)
				conf->conf_timeout = ucl_object_toint(obj);
			else {
				log_warnx("\"timeout\" property value is not integer");
				return (1);
			}
		}

		if (!strcmp(key, "maxproc")) {
			if (obj->type == UCL_INT)
				conf->conf_maxproc = ucl_object_toint(obj);
			else {
				log_warnx("\"maxproc\" property value is not integer");
				return (1);
			}
		}

		if (!strcmp(key, "pidfile")) {
			if (obj->type == UCL_STRING)
				conf->conf_pidfile_path = strdup(
				    ucl_object_tostring(obj));
			else {
				log_warnx("\"pidfile\" property value is not string");
				return (1);
			}
		}

		if (!strcmp(key, "isns-server")) {
			if (obj->type == UCL_ARRAY) {
				iter = NULL;
				while ((child = ucl_iterate_object(obj, &iter,
				    true))) {
					if (child->type != UCL_STRING)
						return (1);

					err = isns_new(conf,
					    ucl_object_tostring(child));
					if (err != 0) {
						return (1);
					}
				}
			} else {
				log_warnx("\"isns-server\" property value is "
				    "not an array");
				return (1);
			}
		}

		if (!strcmp(key, "isns-period")) {
			if (obj->type == UCL_INT)
				conf->conf_timeout = ucl_object_toint(obj);
			else {
				log_warnx("\"isns-period\" property value is not integer");
				return (1);
			}
		}			

		if (!strcmp(key, "isns-timeout")) {
			if (obj->type == UCL_INT)
				conf->conf_timeout = ucl_object_toint(obj);
			else {
				log_warnx("\"isns-timeout\" property value is not integer");
				return (1);
			}
		}

		if (!strcmp(key, "auth-group")) {
			if (obj->type == UCL_OBJECT) {
				iter = NULL;
				while ((child = ucl_iterate_object(obj, &iter, true))) {
					uclparse_auth_group(ucl_object_key(child), child);
				}
			} else {
				log_warnx("\"auth-group\" section is not an object");
				return (1);
			}
		}

		if (!strcmp(key, "portal-group")) {
			if (obj->type == UCL_OBJECT) {
				iter = NULL;
				while ((child = ucl_iterate_object(obj, &iter, true))) {
					uclparse_portal_group(ucl_object_key(child), child);
				}
			} else {
				log_warnx("\"portal-group\" section is not an object");
				return (1);
			}
		}

		if (!strcmp(key, "lun")) {
			if (obj->type == UCL_OBJECT) {
				iter = NULL;
				while ((child = ucl_iterate_object(obj, &iter, true))) {
					uclparse_lun(ucl_object_key(child), child);
				}
			} else {
				log_warnx("\"lun\" section is not an object");
				return (1);
			}
		}
	}

	/* Pass 2 - targets */
	it = NULL;
	while ((obj = ucl_iterate_object(top, &it, true))) {
		const char *key = ucl_object_key(obj);

		if (!strcmp(key, "target")) {
			if (obj->type == UCL_OBJECT) {
				iter = NULL;
				while ((child = ucl_iterate_object(obj, &iter,
				    true))) {
					uclparse_target(ucl_object_key(child),
					    child);
				}
			} else {
				log_warnx("\"target\" section is not an object");
				return (1);
			}
		}
	}

	return (0);
}
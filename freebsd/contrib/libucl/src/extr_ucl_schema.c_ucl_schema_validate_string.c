#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ type; scalar_t__ len; } ;
typedef  TYPE_1__ ucl_object_t ;
typedef  int /*<<< orphan*/ * ucl_object_iter_t ;
struct ucl_schema_error {int dummy; } ;
typedef  int /*<<< orphan*/  regex_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int REG_EXTENDED ; 
 int REG_NOSUB ; 
 scalar_t__ UCL_INT ; 
 int /*<<< orphan*/  UCL_SCHEMA_CONSTRAINT ; 
 int /*<<< orphan*/  UCL_SCHEMA_INVALID_SCHEMA ; 
 scalar_t__ UCL_STRING ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ regexec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* ucl_object_iterate (TYPE_1__ const*,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  ucl_object_key (TYPE_1__ const*) ; 
 scalar_t__ ucl_object_toint (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ucl_object_tostring (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ucl_schema_create_error (struct ucl_schema_error*,int /*<<< orphan*/ ,TYPE_1__ const*,char*,scalar_t__,...) ; 

__attribute__((used)) static bool
ucl_schema_validate_string (const ucl_object_t *schema,
		const ucl_object_t *obj, struct ucl_schema_error *err)
{
	const ucl_object_t *elt;
	ucl_object_iter_t iter = NULL;
	bool ret = true;
	int64_t constraint;
#ifdef HAVE_REGEX_H
	regex_t re;
#endif

	while (ret && (elt = ucl_object_iterate (schema, &iter, true)) != NULL) {
		if (elt->type == UCL_INT &&
			strcmp (ucl_object_key (elt), "maxLength") == 0) {
			constraint = ucl_object_toint (elt);
			if (obj->len > constraint) {
				ucl_schema_create_error (err, UCL_SCHEMA_CONSTRAINT, obj,
						"string is too big: %.3f, maximum is: %.3f",
						obj->len, constraint);
				ret = false;
				break;
			}
		}
		else if (elt->type == UCL_INT &&
				strcmp (ucl_object_key (elt), "minLength") == 0) {
			constraint = ucl_object_toint (elt);
			if (obj->len < constraint) {
				ucl_schema_create_error (err, UCL_SCHEMA_CONSTRAINT, obj,
						"string is too short: %.3f, minimum is: %.3f",
						obj->len, constraint);
				ret = false;
				break;
			}
		}
#ifdef HAVE_REGEX_H
		else if (elt->type == UCL_STRING &&
				strcmp (ucl_object_key (elt), "pattern") == 0) {
			if (regcomp (&re, ucl_object_tostring (elt),
					REG_EXTENDED | REG_NOSUB) != 0) {
				ucl_schema_create_error (err, UCL_SCHEMA_INVALID_SCHEMA, elt,
						"cannot compile pattern %s", ucl_object_tostring (elt));
				ret = false;
				break;
			}
			if (regexec (&re, ucl_object_tostring (obj), 0, NULL, 0) != 0) {
				ucl_schema_create_error (err, UCL_SCHEMA_CONSTRAINT, obj,
						"string doesn't match regexp %s",
						ucl_object_tostring (elt));
				ret = false;
			}
			regfree (&re);
		}
#endif
	}

	return ret;
}
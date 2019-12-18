#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ type; scalar_t__ len; } ;
typedef  TYPE_1__ ucl_object_t ;
typedef  int /*<<< orphan*/ * ucl_object_iter_t ;
struct ucl_schema_error {int dummy; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ UCL_ARRAY ; 
 scalar_t__ UCL_BOOLEAN ; 
 scalar_t__ UCL_OBJECT ; 
 int /*<<< orphan*/  UCL_SCHEMA_CONSTRAINT ; 
 int /*<<< orphan*/  UCL_SCHEMA_INVALID_SCHEMA ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* ucl_array_find_index (TYPE_1__ const*,unsigned int) ; 
 TYPE_1__* ucl_array_head (TYPE_1__ const*) ; 
 TYPE_1__* ucl_object_iterate (TYPE_1__ const*,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  ucl_object_key (TYPE_1__ const*) ; 
 int ucl_object_toboolean (TYPE_1__ const*) ; 
 scalar_t__ ucl_object_toint_safe (TYPE_1__ const*,scalar_t__*) ; 
 int ucl_schema_array_is_unique (TYPE_1__ const*,struct ucl_schema_error*) ; 
 int /*<<< orphan*/  ucl_schema_create_error (struct ucl_schema_error*,int /*<<< orphan*/ ,TYPE_1__ const*,char*,...) ; 
 int ucl_schema_validate (TYPE_1__ const*,TYPE_1__ const*,int,struct ucl_schema_error*,TYPE_1__ const*,TYPE_1__*) ; 

__attribute__((used)) static bool
ucl_schema_validate_array (const ucl_object_t *schema,
		const ucl_object_t *obj, struct ucl_schema_error *err,
		const ucl_object_t *root,
		ucl_object_t *ext_ref)
{
	const ucl_object_t *elt, *it, *found, *additional_schema = NULL,
			*first_unvalidated = NULL;
	ucl_object_iter_t iter = NULL, piter = NULL;
	bool ret = true, allow_additional = true, need_unique = false;
	int64_t minmax;
	unsigned int idx = 0;

	while (ret && (elt = ucl_object_iterate (schema, &iter, true)) != NULL) {
		if (strcmp (ucl_object_key (elt), "items") == 0) {
			if (elt->type == UCL_ARRAY) {
				found = ucl_array_head (obj);
				while (ret && (it = ucl_object_iterate (elt, &piter, true)) != NULL) {
					if (found) {
						ret = ucl_schema_validate (it, found, false, err,
								root, ext_ref);
						found = ucl_array_find_index (obj, ++idx);
					}
				}
				if (found != NULL) {
					/* The first element that is not validated */
					first_unvalidated = found;
				}
			}
			else if (elt->type == UCL_OBJECT) {
				/* Validate all items using the specified schema */
				while (ret && (it = ucl_object_iterate (obj, &piter, true)) != NULL) {
					ret = ucl_schema_validate (elt, it, false, err, root,
							ext_ref);
				}
			}
			else {
				ucl_schema_create_error (err, UCL_SCHEMA_INVALID_SCHEMA, elt,
						"items attribute is invalid in schema");
				ret = false;
				break;
			}
		}
		else if (strcmp (ucl_object_key (elt), "additionalItems") == 0) {
			if (elt->type == UCL_BOOLEAN) {
				if (!ucl_object_toboolean (elt)) {
					/* Deny additional fields completely */
					allow_additional = false;
				}
			}
			else if (elt->type == UCL_OBJECT) {
				/* Define validator for additional fields */
				additional_schema = elt;
			}
			else {
				ucl_schema_create_error (err, UCL_SCHEMA_INVALID_SCHEMA, elt,
						"additionalItems attribute is invalid in schema");
				ret = false;
				break;
			}
		}
		else if (elt->type == UCL_BOOLEAN &&
				strcmp (ucl_object_key (elt), "uniqueItems") == 0) {
			need_unique = ucl_object_toboolean (elt);
		}
		else if (strcmp (ucl_object_key (elt), "minItems") == 0
				&& ucl_object_toint_safe (elt, &minmax)) {
			if (obj->len < minmax) {
				ucl_schema_create_error (err, UCL_SCHEMA_CONSTRAINT, obj,
						"array has not enough items: %u, minimum is: %u",
						obj->len, (unsigned)minmax);
				ret = false;
				break;
			}
		}
		else if (strcmp (ucl_object_key (elt), "maxItems") == 0
				&& ucl_object_toint_safe (elt, &minmax)) {
			if (obj->len > minmax) {
				ucl_schema_create_error (err, UCL_SCHEMA_CONSTRAINT, obj,
						"array has too many items: %u, maximum is: %u",
						obj->len, (unsigned)minmax);
				ret = false;
				break;
			}
		}
	}

	if (ret) {
		/* Additional properties */
		if (!allow_additional || additional_schema != NULL) {
			if (first_unvalidated != NULL) {
				if (!allow_additional) {
					ucl_schema_create_error (err, UCL_SCHEMA_CONSTRAINT, obj,
							"array has undefined item");
					ret = false;
				}
				else if (additional_schema != NULL) {
					elt = ucl_array_find_index (obj, idx);
					while (elt) {
						if (!ucl_schema_validate (additional_schema, elt, false,
								err, root, ext_ref)) {
							ret = false;
							break;
						}
						elt = ucl_array_find_index (obj, idx ++);
					}
				}
			}
		}
		/* Required properties */
		if (ret && need_unique) {
			ret = ucl_schema_array_is_unique (obj, err);
		}
	}

	return ret;
}
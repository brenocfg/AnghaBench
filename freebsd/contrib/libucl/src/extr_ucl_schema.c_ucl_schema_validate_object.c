#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {scalar_t__ type; scalar_t__ len; } ;
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
 int /*<<< orphan*/  UCL_SCHEMA_MISSING_PROPERTY ; 
 scalar_t__ strcmp (char*,char*) ; 
 TYPE_1__* ucl_object_iterate (TYPE_1__ const*,int /*<<< orphan*/ **,int) ; 
 char* ucl_object_key (TYPE_1__ const*) ; 
 TYPE_1__* ucl_object_lookup (TYPE_1__ const*,char*) ; 
 int /*<<< orphan*/  ucl_object_toboolean (TYPE_1__ const*) ; 
 scalar_t__ ucl_object_toint_safe (TYPE_1__ const*,scalar_t__*) ; 
 char* ucl_object_tostring (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ucl_schema_create_error (struct ucl_schema_error*,int /*<<< orphan*/ ,TYPE_1__ const*,char*,...) ; 
 TYPE_1__* ucl_schema_test_pattern (TYPE_1__ const*,char*,int) ; 
 int ucl_schema_validate (TYPE_1__ const*,TYPE_1__ const*,int,struct ucl_schema_error*,TYPE_1__ const*,TYPE_1__*) ; 
 int ucl_schema_validate_dependencies (TYPE_1__ const*,TYPE_1__ const*,struct ucl_schema_error*,TYPE_1__ const*,TYPE_1__*) ; 

__attribute__((used)) static bool
ucl_schema_validate_object (const ucl_object_t *schema,
		const ucl_object_t *obj, struct ucl_schema_error *err,
		const ucl_object_t *root,
		ucl_object_t *ext_ref)
{
	const ucl_object_t *elt, *prop, *found, *additional_schema = NULL,
			*required = NULL, *pat, *pelt;
	ucl_object_iter_t iter = NULL, piter = NULL;
	bool ret = true, allow_additional = true;
	int64_t minmax;

	while (ret && (elt = ucl_object_iterate (schema, &iter, true)) != NULL) {
		if (elt->type == UCL_OBJECT &&
				strcmp (ucl_object_key (elt), "properties") == 0) {
			piter = NULL;
			while (ret && (prop = ucl_object_iterate (elt, &piter, true)) != NULL) {
				found = ucl_object_lookup (obj, ucl_object_key (prop));
				if (found) {
					ret = ucl_schema_validate (prop, found, true, err, root,
							ext_ref);
				}
			}
		}
		else if (strcmp (ucl_object_key (elt), "additionalProperties") == 0) {
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
						"additionalProperties attribute is invalid in schema");
				ret = false;
				break;
			}
		}
		else if (strcmp (ucl_object_key (elt), "required") == 0) {
			if (elt->type == UCL_ARRAY) {
				required = elt;
			}
			else {
				ucl_schema_create_error (err, UCL_SCHEMA_INVALID_SCHEMA, elt,
						"required attribute is invalid in schema");
				ret = false;
				break;
			}
		}
		else if (strcmp (ucl_object_key (elt), "minProperties") == 0
				&& ucl_object_toint_safe (elt, &minmax)) {
			if (obj->len < minmax) {
				ucl_schema_create_error (err, UCL_SCHEMA_CONSTRAINT, obj,
						"object has not enough properties: %u, minimum is: %u",
						obj->len, (unsigned)minmax);
				ret = false;
				break;
			}
		}
		else if (strcmp (ucl_object_key (elt), "maxProperties") == 0
				&& ucl_object_toint_safe (elt, &minmax)) {
			if (obj->len > minmax) {
				ucl_schema_create_error (err, UCL_SCHEMA_CONSTRAINT, obj,
						"object has too many properties: %u, maximum is: %u",
						obj->len, (unsigned)minmax);
				ret = false;
				break;
			}
		}
		else if (strcmp (ucl_object_key (elt), "patternProperties") == 0) {
			const ucl_object_t *vobj;
			ucl_object_iter_t viter;
			piter = NULL;
			while (ret && (prop = ucl_object_iterate (elt, &piter, true)) != NULL) {
				viter = NULL;
				while (ret && (vobj = ucl_object_iterate (obj, &viter, true)) != NULL) {
					found = ucl_schema_test_pattern (vobj, ucl_object_key (prop), false);
					if (found) {
						ret = ucl_schema_validate (prop, found, true, err, root,
								ext_ref);
					}
				}
			}
		}
		else if (elt->type == UCL_OBJECT &&
				strcmp (ucl_object_key (elt), "dependencies") == 0) {
			ret = ucl_schema_validate_dependencies (elt, obj, err, root,
					ext_ref);
		}
	}

	if (ret) {
		/* Additional properties */
		if (!allow_additional || additional_schema != NULL) {
			/* Check if we have exactly the same properties in schema and object */
			iter = NULL;
			prop = ucl_object_lookup (schema, "properties");
			while ((elt = ucl_object_iterate (obj, &iter, true)) != NULL) {
				found = ucl_object_lookup (prop, ucl_object_key (elt));
				if (found == NULL) {
					/* Try patternProperties */
					piter = NULL;
					pat = ucl_object_lookup (schema, "patternProperties");
					while ((pelt = ucl_object_iterate (pat, &piter, true)) != NULL) {
						found = ucl_schema_test_pattern (obj, ucl_object_key (pelt), true);
						if (found != NULL) {
							break;
						}
					}
				}
				if (found == NULL) {
					if (!allow_additional) {
						ucl_schema_create_error (err, UCL_SCHEMA_CONSTRAINT, obj,
								"object has non-allowed property %s",
								ucl_object_key (elt));
						ret = false;
						break;
					}
					else if (additional_schema != NULL) {
						if (!ucl_schema_validate (additional_schema, elt,
								true, err, root, ext_ref)) {
							ret = false;
							break;
						}
					}
				}
			}
		}
		/* Required properties */
		if (required != NULL) {
			iter = NULL;
			while ((elt = ucl_object_iterate (required, &iter, true)) != NULL) {
				if (ucl_object_lookup (obj, ucl_object_tostring (elt)) == NULL) {
					ucl_schema_create_error (err, UCL_SCHEMA_MISSING_PROPERTY, obj,
							"object has missing property %s",
							ucl_object_tostring (elt));
					ret = false;
					break;
				}
			}
		}
	}


	return ret;
}
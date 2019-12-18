#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ type; } ;
typedef  TYPE_1__ ucl_object_t ;
typedef  int /*<<< orphan*/ * ucl_object_iter_t ;
struct ucl_schema_error {int dummy; } ;

/* Variables and functions */
 scalar_t__ UCL_BOOLEAN ; 
 scalar_t__ UCL_FLOAT ; 
 scalar_t__ UCL_INT ; 
 int /*<<< orphan*/  UCL_SCHEMA_CONSTRAINT ; 
 int /*<<< orphan*/  UCL_SCHEMA_INVALID_SCHEMA ; 
 double const fabs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remainder (double,double) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* ucl_object_iterate (TYPE_1__ const*,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  ucl_object_key (TYPE_1__ const*) ; 
 TYPE_1__* ucl_object_lookup (TYPE_1__ const*,char*) ; 
 int ucl_object_toboolean (TYPE_1__ const*) ; 
 double ucl_object_todouble (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ucl_schema_create_error (struct ucl_schema_error*,int /*<<< orphan*/ ,TYPE_1__ const*,char*,...) ; 

__attribute__((used)) static bool
ucl_schema_validate_number (const ucl_object_t *schema,
		const ucl_object_t *obj, struct ucl_schema_error *err)
{
	const ucl_object_t *elt, *test;
	ucl_object_iter_t iter = NULL;
	bool ret = true, exclusive = false;
	double constraint, val;
	const double alpha = 1e-16;

	while (ret && (elt = ucl_object_iterate (schema, &iter, true)) != NULL) {
		if ((elt->type == UCL_FLOAT || elt->type == UCL_INT) &&
				strcmp (ucl_object_key (elt), "multipleOf") == 0) {
			constraint = ucl_object_todouble (elt);
			if (constraint <= 0) {
				ucl_schema_create_error (err, UCL_SCHEMA_INVALID_SCHEMA, elt,
						"multipleOf must be greater than zero");
				ret = false;
				break;
			}
			val = ucl_object_todouble (obj);
			if (fabs (remainder (val, constraint)) > alpha) {
				ucl_schema_create_error (err, UCL_SCHEMA_CONSTRAINT, obj,
						"number %.4f is not multiple of %.4f, remainder is %.7f",
						val, constraint);
				ret = false;
				break;
			}
		}
		else if ((elt->type == UCL_FLOAT || elt->type == UCL_INT) &&
			strcmp (ucl_object_key (elt), "maximum") == 0) {
			constraint = ucl_object_todouble (elt);
			test = ucl_object_lookup (schema, "exclusiveMaximum");
			if (test && test->type == UCL_BOOLEAN) {
				exclusive = ucl_object_toboolean (test);
			}
			val = ucl_object_todouble (obj);
			if (val > constraint || (exclusive && val >= constraint)) {
				ucl_schema_create_error (err, UCL_SCHEMA_CONSTRAINT, obj,
						"number is too big: %.3f, maximum is: %.3f",
						val, constraint);
				ret = false;
				break;
			}
		}
		else if ((elt->type == UCL_FLOAT || elt->type == UCL_INT) &&
				strcmp (ucl_object_key (elt), "minimum") == 0) {
			constraint = ucl_object_todouble (elt);
			test = ucl_object_lookup (schema, "exclusiveMinimum");
			if (test && test->type == UCL_BOOLEAN) {
				exclusive = ucl_object_toboolean (test);
			}
			val = ucl_object_todouble (obj);
			if (val < constraint || (exclusive && val <= constraint)) {
				ucl_schema_create_error (err, UCL_SCHEMA_CONSTRAINT, obj,
						"number is too small: %.3f, minimum is: %.3f",
						val, constraint);
				ret = false;
				break;
			}
		}
	}

	return ret;
}
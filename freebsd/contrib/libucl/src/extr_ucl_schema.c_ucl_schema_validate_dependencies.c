#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ type; } ;
typedef  TYPE_1__ ucl_object_t ;
typedef  int /*<<< orphan*/ * ucl_object_iter_t ;
struct ucl_schema_error {int dummy; } ;

/* Variables and functions */
 scalar_t__ UCL_ARRAY ; 
 scalar_t__ UCL_OBJECT ; 
 int /*<<< orphan*/  UCL_SCHEMA_MISSING_DEPENDENCY ; 
 TYPE_1__* ucl_object_iterate (TYPE_1__ const*,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  ucl_object_key (TYPE_1__ const*) ; 
 TYPE_1__* ucl_object_lookup (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucl_object_tostring (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ucl_schema_create_error (struct ucl_schema_error*,int /*<<< orphan*/ ,TYPE_1__ const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ucl_schema_validate (TYPE_1__ const*,TYPE_1__ const*,int,struct ucl_schema_error*,TYPE_1__ const*,TYPE_1__*) ; 

__attribute__((used)) static bool
ucl_schema_validate_dependencies (const ucl_object_t *deps,
		const ucl_object_t *obj, struct ucl_schema_error *err,
		const ucl_object_t *root,
		ucl_object_t *ext_ref)
{
	const ucl_object_t *elt, *cur, *cur_dep;
	ucl_object_iter_t iter = NULL, piter;
	bool ret = true;

	while (ret && (cur = ucl_object_iterate (deps, &iter, true)) != NULL) {
		elt = ucl_object_lookup (obj, ucl_object_key (cur));
		if (elt != NULL) {
			/* Need to check dependencies */
			if (cur->type == UCL_ARRAY) {
				piter = NULL;
				while (ret && (cur_dep = ucl_object_iterate (cur, &piter, true)) != NULL) {
					if (ucl_object_lookup (obj, ucl_object_tostring (cur_dep)) == NULL) {
						ucl_schema_create_error (err, UCL_SCHEMA_MISSING_DEPENDENCY, elt,
								"dependency %s is missing for key %s",
								ucl_object_tostring (cur_dep), ucl_object_key (cur));
						ret = false;
						break;
					}
				}
			}
			else if (cur->type == UCL_OBJECT) {
				ret = ucl_schema_validate (cur, obj, true, err, root, ext_ref);
			}
		}
	}

	return ret;
}
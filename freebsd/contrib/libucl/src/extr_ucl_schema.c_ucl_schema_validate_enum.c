#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ucl_object_t ;
typedef  int /*<<< orphan*/ * ucl_object_iter_t ;
struct ucl_schema_error {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCL_SCHEMA_CONSTRAINT ; 
 scalar_t__ ucl_object_compare (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ucl_object_iterate (int /*<<< orphan*/  const*,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  ucl_schema_create_error (struct ucl_schema_error*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char*) ; 

__attribute__((used)) static bool
ucl_schema_validate_enum (const ucl_object_t *en, const ucl_object_t *obj,
		struct ucl_schema_error *err)
{
	ucl_object_iter_t iter = NULL;
	const ucl_object_t *elt;
	bool ret = false;

	while ((elt = ucl_object_iterate (en, &iter, true)) != NULL) {
		if (ucl_object_compare (elt, obj) == 0) {
			ret = true;
			break;
		}
	}

	if (!ret) {
		ucl_schema_create_error (err, UCL_SCHEMA_CONSTRAINT, obj,
				"object is not one of enumerated patterns");
	}

	return ret;
}
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
struct ucl_schema_error {char* msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCL_EMIT_CONFIG ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 char* ucl_object_emit (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ucl_object_lookup (int /*<<< orphan*/  const*,char*) ; 
 int ucl_object_toboolean (int /*<<< orphan*/  const*) ; 
 char* ucl_object_tostring (int /*<<< orphan*/  const*) ; 
 int ucl_object_validate (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,struct ucl_schema_error*) ; 

__attribute__((used)) static bool
perform_test (const ucl_object_t *schema, const ucl_object_t *obj,
		struct ucl_schema_error *err)
{
	const ucl_object_t *valid, *data, *description;
	bool match;

	data = ucl_object_lookup (obj, "data");
	description = ucl_object_lookup (obj, "description");
	valid = ucl_object_lookup (obj, "valid");

	if (data == NULL || description == NULL || valid == NULL) {
		fprintf (stdout, "Bad test case\n");
		return false;
	}

	match = ucl_object_validate (schema, data, err);
	if (match != ucl_object_toboolean (valid)) {
		fprintf (stdout, "Test case '%s' failed (expected %s): '%s'\n",
				ucl_object_tostring (description),
				ucl_object_toboolean (valid) ? "valid" : "invalid",
						err->msg);
		fprintf (stdout, "%s\n", ucl_object_emit (data, UCL_EMIT_CONFIG));
		fprintf (stdout, "%s\n", ucl_object_emit (schema, UCL_EMIT_CONFIG));
		return false;
	}

	return true;
}
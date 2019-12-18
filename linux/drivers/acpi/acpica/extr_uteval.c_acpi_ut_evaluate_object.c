#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int type; } ;
union acpi_operand_object {TYPE_1__ common; } ;
typedef  int u32 ;
struct acpi_namespace_node {int dummy; } ;
struct acpi_evaluate_info {char const* relative_pathname; union acpi_operand_object* return_object; struct acpi_namespace_node* prefix_node; } ;
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 struct acpi_evaluate_info* ACPI_ALLOCATE_ZEROED (int) ; 
 int ACPI_BTYPE_BUFFER ; 
 int ACPI_BTYPE_INTEGER ; 
 int ACPI_BTYPE_PACKAGE ; 
 int ACPI_BTYPE_STRING ; 
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR_METHOD (char*,struct acpi_namespace_node*,char const*,scalar_t__) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FREE (struct acpi_evaluate_info*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
#define  ACPI_TYPE_BUFFER 131 
#define  ACPI_TYPE_INTEGER 130 
#define  ACPI_TYPE_PACKAGE 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AE_NOT_EXIST ; 
 scalar_t__ AE_NOT_FOUND ; 
 scalar_t__ AE_NO_MEMORY ; 
 scalar_t__ AE_TYPE ; 
 scalar_t__ acpi_gbl_enable_interpreter_slack ; 
 scalar_t__ acpi_ns_evaluate (struct acpi_evaluate_info*) ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ut_get_object_type_name (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 
 int /*<<< orphan*/  ut_evaluate_object ; 

acpi_status
acpi_ut_evaluate_object(struct acpi_namespace_node *prefix_node,
			const char *path,
			u32 expected_return_btypes,
			union acpi_operand_object **return_desc)
{
	struct acpi_evaluate_info *info;
	acpi_status status;
	u32 return_btype;

	ACPI_FUNCTION_TRACE(ut_evaluate_object);

	/* Allocate the evaluation information block */

	info = ACPI_ALLOCATE_ZEROED(sizeof(struct acpi_evaluate_info));
	if (!info) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	info->prefix_node = prefix_node;
	info->relative_pathname = path;

	/* Evaluate the object/method */

	status = acpi_ns_evaluate(info);
	if (ACPI_FAILURE(status)) {
		if (status == AE_NOT_FOUND) {
			ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
					  "[%4.4s.%s] was not found\n",
					  acpi_ut_get_node_name(prefix_node),
					  path));
		} else {
			ACPI_ERROR_METHOD("Method execution failed",
					  prefix_node, path, status);
		}

		goto cleanup;
	}

	/* Did we get a return object? */

	if (!info->return_object) {
		if (expected_return_btypes) {
			ACPI_ERROR_METHOD("No object was returned from",
					  prefix_node, path, AE_NOT_EXIST);

			status = AE_NOT_EXIST;
		}

		goto cleanup;
	}

	/* Map the return object type to the bitmapped type */

	switch ((info->return_object)->common.type) {
	case ACPI_TYPE_INTEGER:

		return_btype = ACPI_BTYPE_INTEGER;
		break;

	case ACPI_TYPE_BUFFER:

		return_btype = ACPI_BTYPE_BUFFER;
		break;

	case ACPI_TYPE_STRING:

		return_btype = ACPI_BTYPE_STRING;
		break;

	case ACPI_TYPE_PACKAGE:

		return_btype = ACPI_BTYPE_PACKAGE;
		break;

	default:

		return_btype = 0;
		break;
	}

	if ((acpi_gbl_enable_interpreter_slack) && (!expected_return_btypes)) {
		/*
		 * We received a return object, but one was not expected. This can
		 * happen frequently if the "implicit return" feature is enabled.
		 * Just delete the return object and return AE_OK.
		 */
		acpi_ut_remove_reference(info->return_object);
		goto cleanup;
	}

	/* Is the return object one of the expected types? */

	if (!(expected_return_btypes & return_btype)) {
		ACPI_ERROR_METHOD("Return object type is incorrect",
				  prefix_node, path, AE_TYPE);

		ACPI_ERROR((AE_INFO,
			    "Type returned from %s was incorrect: %s, expected Btypes: 0x%X",
			    path,
			    acpi_ut_get_object_type_name(info->return_object),
			    expected_return_btypes));

		/* On error exit, we must delete the return object */

		acpi_ut_remove_reference(info->return_object);
		status = AE_TYPE;
		goto cleanup;
	}

	/* Object type is OK, return it */

	*return_desc = info->return_object;

cleanup:
	ACPI_FREE(info);
	return_ACPI_STATUS(status);
}
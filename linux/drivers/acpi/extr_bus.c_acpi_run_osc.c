#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int length; int /*<<< orphan*/ * pointer; } ;
struct TYPE_5__ {int value; } ;
union acpi_object {scalar_t__ type; TYPE_3__ buffer; TYPE_1__ integer; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_8__ {int length; int /*<<< orphan*/ * pointer; } ;
struct TYPE_6__ {int length; int /*<<< orphan*/ * pointer; } ;
struct acpi_osc_context {int rev; TYPE_4__ ret; TYPE_2__ cap; int /*<<< orphan*/  uuid_str; } ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
struct acpi_buffer {int member_0; union acpi_object* pointer; int /*<<< orphan*/  length; int /*<<< orphan*/ * member_1; } ;
typedef  int /*<<< orphan*/  guid_t ;
typedef  scalar_t__ acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 void* ACPI_TYPE_INTEGER ; 
 scalar_t__ AE_ERROR ; 
 scalar_t__ AE_NO_MEMORY ; 
 scalar_t__ AE_NULL_OBJECT ; 
 scalar_t__ AE_OK ; 
 scalar_t__ AE_SUPPORT ; 
 scalar_t__ AE_TYPE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int OSC_CAPABILITIES_MASK_ERROR ; 
 int OSC_INVALID_REVISION_ERROR ; 
 int OSC_INVALID_UUID_ERROR ; 
 size_t OSC_QUERY_DWORD ; 
 int OSC_QUERY_ENABLE ; 
 int OSC_REQUEST_ERROR ; 
 scalar_t__ acpi_evaluate_object (int /*<<< orphan*/ ,char*,struct acpi_object_list*,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_print_osc_error (int /*<<< orphan*/ ,struct acpi_osc_context*,char*) ; 
 scalar_t__ guid_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

acpi_status acpi_run_osc(acpi_handle handle, struct acpi_osc_context *context)
{
	acpi_status status;
	struct acpi_object_list input;
	union acpi_object in_params[4];
	union acpi_object *out_obj;
	guid_t guid;
	u32 errors;
	struct acpi_buffer output = {ACPI_ALLOCATE_BUFFER, NULL};

	if (!context)
		return AE_ERROR;
	if (guid_parse(context->uuid_str, &guid))
		return AE_ERROR;
	context->ret.length = ACPI_ALLOCATE_BUFFER;
	context->ret.pointer = NULL;

	/* Setting up input parameters */
	input.count = 4;
	input.pointer = in_params;
	in_params[0].type 		= ACPI_TYPE_BUFFER;
	in_params[0].buffer.length 	= 16;
	in_params[0].buffer.pointer	= (u8 *)&guid;
	in_params[1].type 		= ACPI_TYPE_INTEGER;
	in_params[1].integer.value 	= context->rev;
	in_params[2].type 		= ACPI_TYPE_INTEGER;
	in_params[2].integer.value	= context->cap.length/sizeof(u32);
	in_params[3].type		= ACPI_TYPE_BUFFER;
	in_params[3].buffer.length 	= context->cap.length;
	in_params[3].buffer.pointer 	= context->cap.pointer;

	status = acpi_evaluate_object(handle, "_OSC", &input, &output);
	if (ACPI_FAILURE(status))
		return status;

	if (!output.length)
		return AE_NULL_OBJECT;

	out_obj = output.pointer;
	if (out_obj->type != ACPI_TYPE_BUFFER
		|| out_obj->buffer.length != context->cap.length) {
		acpi_print_osc_error(handle, context,
			"_OSC evaluation returned wrong type");
		status = AE_TYPE;
		goto out_kfree;
	}
	/* Need to ignore the bit0 in result code */
	errors = *((u32 *)out_obj->buffer.pointer) & ~(1 << 0);
	if (errors) {
		if (errors & OSC_REQUEST_ERROR)
			acpi_print_osc_error(handle, context,
				"_OSC request failed");
		if (errors & OSC_INVALID_UUID_ERROR)
			acpi_print_osc_error(handle, context,
				"_OSC invalid UUID");
		if (errors & OSC_INVALID_REVISION_ERROR)
			acpi_print_osc_error(handle, context,
				"_OSC invalid revision");
		if (errors & OSC_CAPABILITIES_MASK_ERROR) {
			if (((u32 *)context->cap.pointer)[OSC_QUERY_DWORD]
			    & OSC_QUERY_ENABLE)
				goto out_success;
			status = AE_SUPPORT;
			goto out_kfree;
		}
		status = AE_ERROR;
		goto out_kfree;
	}
out_success:
	context->ret.length = out_obj->buffer.length;
	context->ret.pointer = kmemdup(out_obj->buffer.pointer,
				       context->ret.length, GFP_KERNEL);
	if (!context->ret.pointer) {
		status =  AE_NO_MEMORY;
		goto out_kfree;
	}
	status =  AE_OK;

out_kfree:
	kfree(output.pointer);
	if (status != AE_OK)
		context->ret.pointer = NULL;
	return status;
}
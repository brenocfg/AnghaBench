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
struct TYPE_8__ {scalar_t__ (* setup ) (union acpi_operand_object*,int /*<<< orphan*/ ,struct acpi_connection_info*,void**) ;scalar_t__ (* handler ) (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,struct acpi_connection_info*,void*) ;int handler_flags; struct acpi_connection_info* context; } ;
struct TYPE_7__ {scalar_t__ space_id; int flags; union acpi_operand_object* handler; scalar_t__ address; int /*<<< orphan*/  node; } ;
struct TYPE_6__ {void* region_context; } ;
struct TYPE_5__ {scalar_t__ bit_length; scalar_t__ pin_number_index; int /*<<< orphan*/  access_length; int /*<<< orphan*/  resource_length; int /*<<< orphan*/  resource_buffer; } ;
union acpi_operand_object {TYPE_4__ address_space; TYPE_3__ region; TYPE_2__ extra; TYPE_1__ field; } ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct acpi_connection_info {int /*<<< orphan*/  access_length; int /*<<< orphan*/  length; int /*<<< orphan*/  connection; } ;
typedef  scalar_t__ acpi_status ;
typedef  scalar_t__ acpi_physical_address ;
typedef  scalar_t__ (* acpi_adr_space_setup ) (union acpi_operand_object*,int /*<<< orphan*/ ,struct acpi_connection_info*,void**) ;
typedef  scalar_t__ (* acpi_adr_space_handler ) (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,struct acpi_connection_info*,void*) ;

/* Variables and functions */
 int ACPI_ADDR_HANDLER_DEFAULT_INSTALLED ; 
 scalar_t__ ACPI_ADR_SPACE_EC ; 
 scalar_t__ ACPI_ADR_SPACE_GPIO ; 
 scalar_t__ ACPI_ADR_SPACE_GSBUS ; 
 int /*<<< orphan*/  ACPI_DB_OPREGION ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_REGION_ACTIVATE ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AE_NOT_EXIST ; 
 scalar_t__ AE_TIME ; 
 int AOPOBJ_SETUP_COMPLETE ; 
 int /*<<< orphan*/  acpi_ex_enter_interpreter () ; 
 int /*<<< orphan*/  acpi_ex_exit_interpreter () ; 
 union acpi_operand_object* acpi_ns_get_secondary_object (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_get_region_name (scalar_t__) ; 
 int /*<<< orphan*/  ev_address_space_dispatch ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 

acpi_status
acpi_ev_address_space_dispatch(union acpi_operand_object *region_obj,
			       union acpi_operand_object *field_obj,
			       u32 function,
			       u32 region_offset, u32 bit_width, u64 *value)
{
	acpi_status status;
	acpi_adr_space_handler handler;
	acpi_adr_space_setup region_setup;
	union acpi_operand_object *handler_desc;
	union acpi_operand_object *region_obj2;
	void *region_context = NULL;
	struct acpi_connection_info *context;
	acpi_physical_address address;

	ACPI_FUNCTION_TRACE(ev_address_space_dispatch);

	region_obj2 = acpi_ns_get_secondary_object(region_obj);
	if (!region_obj2) {
		return_ACPI_STATUS(AE_NOT_EXIST);
	}

	/* Ensure that there is a handler associated with this region */

	handler_desc = region_obj->region.handler;
	if (!handler_desc) {
		ACPI_ERROR((AE_INFO,
			    "No handler for Region [%4.4s] (%p) [%s]",
			    acpi_ut_get_node_name(region_obj->region.node),
			    region_obj,
			    acpi_ut_get_region_name(region_obj->region.
						    space_id)));

		return_ACPI_STATUS(AE_NOT_EXIST);
	}

	context = handler_desc->address_space.context;

	/*
	 * It may be the case that the region has never been initialized.
	 * Some types of regions require special init code
	 */
	if (!(region_obj->region.flags & AOPOBJ_SETUP_COMPLETE)) {

		/* This region has not been initialized yet, do it */

		region_setup = handler_desc->address_space.setup;
		if (!region_setup) {

			/* No initialization routine, exit with error */

			ACPI_ERROR((AE_INFO,
				    "No init routine for region(%p) [%s]",
				    region_obj,
				    acpi_ut_get_region_name(region_obj->region.
							    space_id)));
			return_ACPI_STATUS(AE_NOT_EXIST);
		}

		/*
		 * We must exit the interpreter because the region setup will
		 * potentially execute control methods (for example, the _REG method
		 * for this region)
		 */
		acpi_ex_exit_interpreter();

		status = region_setup(region_obj, ACPI_REGION_ACTIVATE,
				      context, &region_context);

		/* Re-enter the interpreter */

		acpi_ex_enter_interpreter();

		/* Check for failure of the Region Setup */

		if (ACPI_FAILURE(status)) {
			ACPI_EXCEPTION((AE_INFO, status,
					"During region initialization: [%s]",
					acpi_ut_get_region_name(region_obj->
								region.
								space_id)));
			return_ACPI_STATUS(status);
		}

		/* Region initialization may have been completed by region_setup */

		if (!(region_obj->region.flags & AOPOBJ_SETUP_COMPLETE)) {
			region_obj->region.flags |= AOPOBJ_SETUP_COMPLETE;

			/*
			 * Save the returned context for use in all accesses to
			 * the handler for this particular region
			 */
			if (!(region_obj2->extra.region_context)) {
				region_obj2->extra.region_context =
				    region_context;
			}
		}
	}

	/* We have everything we need, we can invoke the address space handler */

	handler = handler_desc->address_space.handler;
	address = (region_obj->region.address + region_offset);

	/*
	 * Special handling for generic_serial_bus and general_purpose_io:
	 * There are three extra parameters that must be passed to the
	 * handler via the context:
	 *   1) Connection buffer, a resource template from Connection() op
	 *   2) Length of the above buffer
	 *   3) Actual access length from the access_as() op
	 *
	 * In addition, for general_purpose_io, the Address and bit_width fields
	 * are defined as follows:
	 *   1) Address is the pin number index of the field (bit offset from
	 *      the previous Connection)
	 *   2) bit_width is the actual bit length of the field (number of pins)
	 */
	if ((region_obj->region.space_id == ACPI_ADR_SPACE_GSBUS) &&
	    context && field_obj) {

		/* Get the Connection (resource_template) buffer */

		context->connection = field_obj->field.resource_buffer;
		context->length = field_obj->field.resource_length;
		context->access_length = field_obj->field.access_length;
	}
	if ((region_obj->region.space_id == ACPI_ADR_SPACE_GPIO) &&
	    context && field_obj) {

		/* Get the Connection (resource_template) buffer */

		context->connection = field_obj->field.resource_buffer;
		context->length = field_obj->field.resource_length;
		context->access_length = field_obj->field.access_length;
		address = field_obj->field.pin_number_index;
		bit_width = field_obj->field.bit_length;
	}

	ACPI_DEBUG_PRINT((ACPI_DB_OPREGION,
			  "Handler %p (@%p) Address %8.8X%8.8X [%s]\n",
			  &region_obj->region.handler->address_space, handler,
			  ACPI_FORMAT_UINT64(address),
			  acpi_ut_get_region_name(region_obj->region.
						  space_id)));

	if (!(handler_desc->address_space.handler_flags &
	      ACPI_ADDR_HANDLER_DEFAULT_INSTALLED)) {
		/*
		 * For handlers other than the default (supplied) handlers, we must
		 * exit the interpreter because the handler *might* block -- we don't
		 * know what it will do, so we can't hold the lock on the interpreter.
		 */
		acpi_ex_exit_interpreter();
	}

	/* Call the handler */

	status = handler(function, address, bit_width, value, context,
			 region_obj2->extra.region_context);

	if (ACPI_FAILURE(status)) {
		ACPI_EXCEPTION((AE_INFO, status, "Returned by Handler for [%s]",
				acpi_ut_get_region_name(region_obj->region.
							space_id)));

		/*
		 * Special case for an EC timeout. These are seen so frequently
		 * that an additional error message is helpful
		 */
		if ((region_obj->region.space_id == ACPI_ADR_SPACE_EC) &&
		    (status == AE_TIME)) {
			ACPI_ERROR((AE_INFO,
				    "Timeout from EC hardware or EC device driver"));
		}
	}

	if (!(handler_desc->address_space.handler_flags &
	      ACPI_ADDR_HANDLER_DEFAULT_INSTALLED)) {
		/*
		 * We just returned from a non-default handler, we must re-enter the
		 * interpreter
		 */
		acpi_ex_enter_interpreter();
	}

	return_ACPI_STATUS(status);
}
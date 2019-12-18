#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {union acpi_operand_object* handler; } ;
struct TYPE_5__ {scalar_t__ handler; union acpi_operand_object* next; int /*<<< orphan*/ * setup; void* context; struct acpi_namespace_node* node; int /*<<< orphan*/ * region_list; void* handler_flags; void* space_id; } ;
struct TYPE_4__ {void* type; } ;
union acpi_operand_object {TYPE_3__ common_notify; TYPE_2__ address_space; TYPE_1__ common; } ;
typedef  void* u8 ;
struct acpi_namespace_node {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_object_type ;
typedef  int acpi_adr_space_type ;
typedef  int /*<<< orphan*/ * acpi_adr_space_setup ;
typedef  scalar_t__ acpi_adr_space_handler ;

/* Variables and functions */
 void* ACPI_ADDR_HANDLER_DEFAULT_INSTALLED ; 
#define  ACPI_ADR_SPACE_CMOS 133 
#define  ACPI_ADR_SPACE_DATA_TABLE 132 
#define  ACPI_ADR_SPACE_PCI_BAR_TARGET 131 
#define  ACPI_ADR_SPACE_PCI_CONFIG 130 
#define  ACPI_ADR_SPACE_SYSTEM_IO 129 
#define  ACPI_ADR_SPACE_SYSTEM_MEMORY 128 
 int /*<<< orphan*/  ACPI_DB_OPREGION ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_DEFAULT_HANDLER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_NS_WALK_UNLOCK ; 
 scalar_t__ ACPI_TYPE_ANY ; 
 scalar_t__ ACPI_TYPE_DEVICE ; 
 scalar_t__ ACPI_TYPE_LOCAL_ADDRESS_HANDLER ; 
 scalar_t__ ACPI_TYPE_PROCESSOR ; 
 scalar_t__ ACPI_TYPE_THERMAL ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_ALREADY_EXISTS ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_SAME_HANDLER ; 
 int /*<<< orphan*/ * acpi_ev_cmos_region_setup ; 
 int /*<<< orphan*/ * acpi_ev_default_region_setup ; 
 union acpi_operand_object* acpi_ev_find_region_handler (int,union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ev_install_handler ; 
 int /*<<< orphan*/ * acpi_ev_io_space_region_setup ; 
 int /*<<< orphan*/ * acpi_ev_pci_bar_region_setup ; 
 int /*<<< orphan*/ * acpi_ev_pci_config_region_setup ; 
 int /*<<< orphan*/ * acpi_ev_system_memory_region_setup ; 
 scalar_t__ acpi_ex_cmos_space_handler ; 
 scalar_t__ acpi_ex_data_table_space_handler ; 
 scalar_t__ acpi_ex_pci_bar_space_handler ; 
 scalar_t__ acpi_ex_pci_config_space_handler ; 
 scalar_t__ acpi_ex_system_io_space_handler ; 
 scalar_t__ acpi_ex_system_memory_space_handler ; 
 struct acpi_namespace_node* acpi_gbl_root_node ; 
 int /*<<< orphan*/  acpi_ns_attach_object (struct acpi_namespace_node*,union acpi_operand_object*,scalar_t__) ; 
 union acpi_operand_object* acpi_ns_get_attached_object (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ns_walk_namespace (scalar_t__,struct acpi_namespace_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,union acpi_operand_object*,int /*<<< orphan*/ *) ; 
 union acpi_operand_object* acpi_ut_create_internal_object (scalar_t__) ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ut_get_region_name (int) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ev_install_space_handler ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ev_install_space_handler(struct acpi_namespace_node *node,
			      acpi_adr_space_type space_id,
			      acpi_adr_space_handler handler,
			      acpi_adr_space_setup setup, void *context)
{
	union acpi_operand_object *obj_desc;
	union acpi_operand_object *handler_obj;
	acpi_status status = AE_OK;
	acpi_object_type type;
	u8 flags = 0;

	ACPI_FUNCTION_TRACE(ev_install_space_handler);

	/*
	 * This registration is valid for only the types below and the root.
	 * The root node is where the default handlers get installed.
	 */
	if ((node->type != ACPI_TYPE_DEVICE) &&
	    (node->type != ACPI_TYPE_PROCESSOR) &&
	    (node->type != ACPI_TYPE_THERMAL) && (node != acpi_gbl_root_node)) {
		status = AE_BAD_PARAMETER;
		goto unlock_and_exit;
	}

	if (handler == ACPI_DEFAULT_HANDLER) {
		flags = ACPI_ADDR_HANDLER_DEFAULT_INSTALLED;

		switch (space_id) {
		case ACPI_ADR_SPACE_SYSTEM_MEMORY:

			handler = acpi_ex_system_memory_space_handler;
			setup = acpi_ev_system_memory_region_setup;
			break;

		case ACPI_ADR_SPACE_SYSTEM_IO:

			handler = acpi_ex_system_io_space_handler;
			setup = acpi_ev_io_space_region_setup;
			break;
#ifdef ACPI_PCI_CONFIGURED
		case ACPI_ADR_SPACE_PCI_CONFIG:

			handler = acpi_ex_pci_config_space_handler;
			setup = acpi_ev_pci_config_region_setup;
			break;
#endif
		case ACPI_ADR_SPACE_CMOS:

			handler = acpi_ex_cmos_space_handler;
			setup = acpi_ev_cmos_region_setup;
			break;
#ifdef ACPI_PCI_CONFIGURED
		case ACPI_ADR_SPACE_PCI_BAR_TARGET:

			handler = acpi_ex_pci_bar_space_handler;
			setup = acpi_ev_pci_bar_region_setup;
			break;
#endif
		case ACPI_ADR_SPACE_DATA_TABLE:

			handler = acpi_ex_data_table_space_handler;
			setup = NULL;
			break;

		default:

			status = AE_BAD_PARAMETER;
			goto unlock_and_exit;
		}
	}

	/* If the caller hasn't specified a setup routine, use the default */

	if (!setup) {
		setup = acpi_ev_default_region_setup;
	}

	/* Check for an existing internal object */

	obj_desc = acpi_ns_get_attached_object(node);
	if (obj_desc) {
		/*
		 * The attached device object already exists. Now make sure
		 * the handler is not already installed.
		 */
		handler_obj = acpi_ev_find_region_handler(space_id,
							  obj_desc->
							  common_notify.
							  handler);

		if (handler_obj) {
			if (handler_obj->address_space.handler == handler) {
				/*
				 * It is (relatively) OK to attempt to install the SAME
				 * handler twice. This can easily happen with the
				 * PCI_Config space.
				 */
				status = AE_SAME_HANDLER;
				goto unlock_and_exit;
			} else {
				/* A handler is already installed */

				status = AE_ALREADY_EXISTS;
			}

			goto unlock_and_exit;
		}
	} else {
		ACPI_DEBUG_PRINT((ACPI_DB_OPREGION,
				  "Creating object on Device %p while installing handler\n",
				  node));

		/* obj_desc does not exist, create one */

		if (node->type == ACPI_TYPE_ANY) {
			type = ACPI_TYPE_DEVICE;
		} else {
			type = node->type;
		}

		obj_desc = acpi_ut_create_internal_object(type);
		if (!obj_desc) {
			status = AE_NO_MEMORY;
			goto unlock_and_exit;
		}

		/* Init new descriptor */

		obj_desc->common.type = (u8)type;

		/* Attach the new object to the Node */

		status = acpi_ns_attach_object(node, obj_desc, type);

		/* Remove local reference to the object */

		acpi_ut_remove_reference(obj_desc);

		if (ACPI_FAILURE(status)) {
			goto unlock_and_exit;
		}
	}

	ACPI_DEBUG_PRINT((ACPI_DB_OPREGION,
			  "Installing address handler for region %s(%X) "
			  "on Device %4.4s %p(%p)\n",
			  acpi_ut_get_region_name(space_id), space_id,
			  acpi_ut_get_node_name(node), node, obj_desc));

	/*
	 * Install the handler
	 *
	 * At this point there is no existing handler. Just allocate the object
	 * for the handler and link it into the list.
	 */
	handler_obj =
	    acpi_ut_create_internal_object(ACPI_TYPE_LOCAL_ADDRESS_HANDLER);
	if (!handler_obj) {
		status = AE_NO_MEMORY;
		goto unlock_and_exit;
	}

	/* Init handler obj */

	handler_obj->address_space.space_id = (u8)space_id;
	handler_obj->address_space.handler_flags = flags;
	handler_obj->address_space.region_list = NULL;
	handler_obj->address_space.node = node;
	handler_obj->address_space.handler = handler;
	handler_obj->address_space.context = context;
	handler_obj->address_space.setup = setup;

	/* Install at head of Device.address_space list */

	handler_obj->address_space.next = obj_desc->common_notify.handler;

	/*
	 * The Device object is the first reference on the handler_obj.
	 * Each region that uses the handler adds a reference.
	 */
	obj_desc->common_notify.handler = handler_obj;

	/*
	 * Walk the namespace finding all of the regions this handler will
	 * manage.
	 *
	 * Start at the device and search the branch toward the leaf nodes
	 * until either the leaf is encountered or a device is detected that
	 * has an address handler of the same type.
	 *
	 * In either case, back up and search down the remainder of the branch
	 */
	status = acpi_ns_walk_namespace(ACPI_TYPE_ANY, node,
					ACPI_UINT32_MAX, ACPI_NS_WALK_UNLOCK,
					acpi_ev_install_handler, NULL,
					handler_obj, NULL);

unlock_and_exit:
	return_ACPI_STATUS(status);
}
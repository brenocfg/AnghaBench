#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  type; int /*<<< orphan*/  flags; } ;
struct TYPE_15__ {int /*<<< orphan*/  os_mutex; void* sync_level; struct acpi_namespace_node* node; } ;
struct TYPE_14__ {int /*<<< orphan*/ * pointer; int /*<<< orphan*/  length; } ;
struct TYPE_13__ {int /*<<< orphan*/  value; } ;
struct TYPE_11__ {int /*<<< orphan*/  implementation; } ;
struct TYPE_12__ {TYPE_2__ dispatch; int /*<<< orphan*/  info_flags; void* param_count; } ;
union acpi_operand_object {TYPE_7__ common; TYPE_6__ mutex; TYPE_5__ string; TYPE_4__ integer; TYPE_3__ method; } ;
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_predefined_names {int type; scalar_t__ name; int /*<<< orphan*/ * val; } ;
struct TYPE_10__ {int /*<<< orphan*/  ascii; } ;
struct acpi_namespace_node {int type; void* value; TYPE_8__* parent; struct acpi_namespace_node* peer; int /*<<< orphan*/  descriptor_type; TYPE_1__ name; } ;
typedef  int /*<<< orphan*/ * acpi_string ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_17__ {struct acpi_namespace_node* child; } ;

/* Variables and functions */
 struct acpi_namespace_node* ACPI_ALLOCATE_ZEROED (int) ; 
 int /*<<< orphan*/  ACPI_COPY_NAMESEG (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DESC_TYPE_NAMED ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_METHOD_INTERNAL_ONLY ; 
 int /*<<< orphan*/  ACPI_MTX_NAMESPACE ; 
 int /*<<< orphan*/  ACPI_NS_NO_UPSEARCH ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TO_INTEGER (int /*<<< orphan*/ *) ; 
#define  ACPI_TYPE_INTEGER 131 
#define  ACPI_TYPE_METHOD 130 
#define  ACPI_TYPE_MUTEX 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  AOPOBJ_STATIC_POINTER ; 
 int /*<<< orphan*/  acpi_gbl_create_osi_method ; 
 int /*<<< orphan*/  acpi_gbl_fadt_gpe_device ; 
 union acpi_operand_object* acpi_gbl_global_lock_mutex ; 
 int /*<<< orphan*/  acpi_gbl_global_lock_semaphore ; 
 struct acpi_predefined_names* acpi_gbl_pre_defined_names ; 
 TYPE_8__* acpi_gbl_root_node ; 
 TYPE_8__ acpi_gbl_root_node_struct ; 
 int /*<<< orphan*/  acpi_ns_attach_object (struct acpi_namespace_node*,union acpi_operand_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ns_get_node (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_os_create_mutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_os_create_semaphore (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_os_predefined_override (struct acpi_predefined_names const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  acpi_ut_acquire_mutex (int /*<<< orphan*/ ) ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int) ; 
 int /*<<< orphan*/  acpi_ut_osi_implementation ; 
 int /*<<< orphan*/  acpi_ut_release_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ns_root_initialize ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 

acpi_status acpi_ns_root_initialize(void)
{
	acpi_status status;
	const struct acpi_predefined_names *init_val = NULL;
	struct acpi_namespace_node *new_node;
	struct acpi_namespace_node *prev_node = NULL;
	union acpi_operand_object *obj_desc;
	acpi_string val = NULL;

	ACPI_FUNCTION_TRACE(ns_root_initialize);

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/*
	 * The global root ptr is initially NULL, so a non-NULL value indicates
	 * that acpi_ns_root_initialize() has already been called; just return.
	 */
	if (acpi_gbl_root_node) {
		status = AE_OK;
		goto unlock_and_exit;
	}

	/*
	 * Tell the rest of the subsystem that the root is initialized
	 * (This is OK because the namespace is locked)
	 */
	acpi_gbl_root_node = &acpi_gbl_root_node_struct;

	/* Enter the predefined names in the name table */

	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "Entering predefined entries into namespace\n"));

	/*
	 * Create the initial (default) namespace.
	 * This namespace looks like something similar to this:
	 *
	 *   ACPI Namespace (from Namespace Root):
	 *    0  _GPE Scope        00203160 00
	 *    0  _PR_ Scope        002031D0 00
	 *    0  _SB_ Device       00203240 00 Notify Object: 0020ADD8
	 *    0  _SI_ Scope        002032B0 00
	 *    0  _TZ_ Device       00203320 00
	 *    0  _REV Integer      00203390 00 = 0000000000000002
	 *    0  _OS_ String       00203488 00 Len 14 "Microsoft Windows NT"
	 *    0  _GL_ Mutex        00203580 00 Object 002035F0
	 *    0  _OSI Method       00203678 00 Args 1 Len 0000 Aml 00000000
	 */
	for (init_val = acpi_gbl_pre_defined_names; init_val->name; init_val++) {
		status = AE_OK;

		/* _OSI is optional for now, will be permanent later */

		if (!strcmp(init_val->name, "_OSI")
		    && !acpi_gbl_create_osi_method) {
			continue;
		}

		/*
		 * Create, init, and link the new predefined name
		 * Note: No need to use acpi_ns_lookup here because all the
		 * predefined names are at the root level. It is much easier to
		 * just create and link the new node(s) here.
		 */
		new_node =
		    ACPI_ALLOCATE_ZEROED(sizeof(struct acpi_namespace_node));
		if (!new_node) {
			status = AE_NO_MEMORY;
			goto unlock_and_exit;
		}

		ACPI_COPY_NAMESEG(new_node->name.ascii, init_val->name);
		new_node->descriptor_type = ACPI_DESC_TYPE_NAMED;
		new_node->type = init_val->type;

		if (!prev_node) {
			acpi_gbl_root_node_struct.child = new_node;
		} else {
			prev_node->peer = new_node;
		}

		new_node->parent = &acpi_gbl_root_node_struct;
		prev_node = new_node;

		/*
		 * Name entered successfully. If entry in pre_defined_names[] specifies
		 * an initial value, create the initial value.
		 */
		if (init_val->val) {
			status = acpi_os_predefined_override(init_val, &val);
			if (ACPI_FAILURE(status)) {
				ACPI_ERROR((AE_INFO,
					    "Could not override predefined %s",
					    init_val->name));
			}

			if (!val) {
				val = init_val->val;
			}

			/*
			 * Entry requests an initial value, allocate a
			 * descriptor for it.
			 */
			obj_desc =
			    acpi_ut_create_internal_object(init_val->type);
			if (!obj_desc) {
				status = AE_NO_MEMORY;
				goto unlock_and_exit;
			}

			/*
			 * Convert value string from table entry to
			 * internal representation. Only types actually
			 * used for initial values are implemented here.
			 */
			switch (init_val->type) {
			case ACPI_TYPE_METHOD:

				obj_desc->method.param_count =
				    (u8) ACPI_TO_INTEGER(val);
				obj_desc->common.flags |= AOPOBJ_DATA_VALID;

#if defined (ACPI_ASL_COMPILER)

				/* Save the parameter count for the iASL compiler */

				new_node->value = obj_desc->method.param_count;
#else
				/* Mark this as a very SPECIAL method (_OSI) */

				obj_desc->method.info_flags =
				    ACPI_METHOD_INTERNAL_ONLY;
				obj_desc->method.dispatch.implementation =
				    acpi_ut_osi_implementation;
#endif
				break;

			case ACPI_TYPE_INTEGER:

				obj_desc->integer.value = ACPI_TO_INTEGER(val);
				break;

			case ACPI_TYPE_STRING:

				/* Build an object around the static string */

				obj_desc->string.length = (u32)strlen(val);
				obj_desc->string.pointer = val;
				obj_desc->common.flags |= AOPOBJ_STATIC_POINTER;
				break;

			case ACPI_TYPE_MUTEX:

				obj_desc->mutex.node = new_node;
				obj_desc->mutex.sync_level =
				    (u8) (ACPI_TO_INTEGER(val) - 1);

				/* Create a mutex */

				status =
				    acpi_os_create_mutex(&obj_desc->mutex.
							 os_mutex);
				if (ACPI_FAILURE(status)) {
					acpi_ut_remove_reference(obj_desc);
					goto unlock_and_exit;
				}

				/* Special case for ACPI Global Lock */

				if (strcmp(init_val->name, "_GL_") == 0) {
					acpi_gbl_global_lock_mutex = obj_desc;

					/* Create additional counting semaphore for global lock */

					status =
					    acpi_os_create_semaphore(1, 0,
								     &acpi_gbl_global_lock_semaphore);
					if (ACPI_FAILURE(status)) {
						acpi_ut_remove_reference
						    (obj_desc);
						goto unlock_and_exit;
					}
				}
				break;

			default:

				ACPI_ERROR((AE_INFO,
					    "Unsupported initial type value 0x%X",
					    init_val->type));
				acpi_ut_remove_reference(obj_desc);
				obj_desc = NULL;
				continue;
			}

			/* Store pointer to value descriptor in the Node */

			status = acpi_ns_attach_object(new_node, obj_desc,
						       obj_desc->common.type);

			/* Remove local reference to the object */

			acpi_ut_remove_reference(obj_desc);
		}
	}

unlock_and_exit:
	(void)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);

	/* Save a handle to "_GPE", it is always present */

	if (ACPI_SUCCESS(status)) {
		status = acpi_ns_get_node(NULL, "\\_GPE", ACPI_NS_NO_UPSEARCH,
					  &acpi_gbl_fadt_gpe_device);
	}

	return_ACPI_STATUS(status);
}
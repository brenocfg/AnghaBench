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
typedef  int u32 ;
struct acpi_walk_info {int display_type; int /*<<< orphan*/  debug_level; int /*<<< orphan*/  owner_id; scalar_t__ count; } ;
struct TYPE_2__ {char* ascii; } ;
struct acpi_namespace_node {TYPE_1__ name; } ;
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  char* acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_LOCAL_BUFFER ; 
 int ACPI_DISPLAY_SHORT ; 
 int ACPI_DISPLAY_SUMMARY ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_OWNER_ID_MAX ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_ns_dump_one_object (char*,int,struct acpi_walk_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ns_handle_to_pathname (char*,struct acpi_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,char*) ; 

__attribute__((used)) static acpi_status
acpi_db_walk_and_match_name(acpi_handle obj_handle,
			    u32 nesting_level,
			    void *context, void **return_value)
{
	acpi_status status;
	char *requested_name = (char *)context;
	u32 i;
	struct acpi_buffer buffer;
	struct acpi_walk_info info;

	/* Check for a name match */

	for (i = 0; i < 4; i++) {

		/* Wildcard support */

		if ((requested_name[i] != '?') &&
		    (requested_name[i] != ((struct acpi_namespace_node *)
					   obj_handle)->name.ascii[i])) {

			/* No match, just exit */

			return (AE_OK);
		}
	}

	/* Get the full pathname to this object */

	buffer.length = ACPI_ALLOCATE_LOCAL_BUFFER;
	status = acpi_ns_handle_to_pathname(obj_handle, &buffer, TRUE);
	if (ACPI_FAILURE(status)) {
		acpi_os_printf("Could Not get pathname for object %p\n",
			       obj_handle);
	} else {
		info.count = 0;
		info.owner_id = ACPI_OWNER_ID_MAX;
		info.debug_level = ACPI_UINT32_MAX;
		info.display_type = ACPI_DISPLAY_SUMMARY | ACPI_DISPLAY_SHORT;

		acpi_os_printf("%32s", (char *)buffer.pointer);
		(void)acpi_ns_dump_one_object(obj_handle, nesting_level, &info,
					      NULL);
		ACPI_FREE(buffer.pointer);
	}

	return (AE_OK);
}
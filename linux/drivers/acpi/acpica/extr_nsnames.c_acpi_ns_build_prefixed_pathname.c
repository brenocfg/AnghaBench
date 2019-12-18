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
struct TYPE_2__ {scalar_t__ node; } ;
union acpi_generic_state {TYPE_1__ scope; } ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 char* ACPI_ALLOCATE_ZEROED (scalar_t__) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_ns_externalize_name (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,char**) ; 
 char* acpi_ns_get_normalized_pathname (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ns_normalize_pathname (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

char *acpi_ns_build_prefixed_pathname(union acpi_generic_state *prefix_scope,
				      const char *internal_path)
{
	acpi_status status;
	char *full_path = NULL;
	char *external_path = NULL;
	char *prefix_path = NULL;
	u32 prefix_path_length = 0;

	/* If there is a prefix, get the pathname to it */

	if (prefix_scope && prefix_scope->scope.node) {
		prefix_path =
		    acpi_ns_get_normalized_pathname(prefix_scope->scope.node,
						    TRUE);
		if (prefix_path) {
			prefix_path_length = strlen(prefix_path);
		}
	}

	status = acpi_ns_externalize_name(ACPI_UINT32_MAX, internal_path,
					  NULL, &external_path);
	if (ACPI_FAILURE(status)) {
		goto cleanup;
	}

	/* Merge the prefix path and the path. 2 is for one dot and trailing null */

	full_path =
	    ACPI_ALLOCATE_ZEROED(prefix_path_length + strlen(external_path) +
				 2);
	if (!full_path) {
		goto cleanup;
	}

	/* Don't merge if the External path is already fully qualified */

	if (prefix_path && (*external_path != '\\') && (*external_path != '^')) {
		strcat(full_path, prefix_path);
		if (prefix_path[1]) {
			strcat(full_path, ".");
		}
	}

	acpi_ns_normalize_pathname(external_path);
	strcat(full_path, external_path);

cleanup:
	if (prefix_path) {
		ACPI_FREE(prefix_path);
	}
	if (external_path) {
		ACPI_FREE(external_path);
	}

	return (full_path);
}
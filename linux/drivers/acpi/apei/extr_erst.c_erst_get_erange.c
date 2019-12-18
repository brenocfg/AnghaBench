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
struct erst_erange {void* attr; void* size; void* base; } ;
struct apei_exec_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERST_GET_ERROR_ATTRIBUTES ; 
 int /*<<< orphan*/  ACPI_ERST_GET_ERROR_LENGTH ; 
 int /*<<< orphan*/  ACPI_ERST_GET_ERROR_RANGE ; 
 void* apei_exec_ctx_get_output (struct apei_exec_context*) ; 
 int apei_exec_run (struct apei_exec_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  erst_exec_ctx_init (struct apei_exec_context*) ; 

__attribute__((used)) static int erst_get_erange(struct erst_erange *range)
{
	struct apei_exec_context ctx;
	int rc;

	erst_exec_ctx_init(&ctx);
	rc = apei_exec_run(&ctx, ACPI_ERST_GET_ERROR_RANGE);
	if (rc)
		return rc;
	range->base = apei_exec_ctx_get_output(&ctx);
	rc = apei_exec_run(&ctx, ACPI_ERST_GET_ERROR_LENGTH);
	if (rc)
		return rc;
	range->size = apei_exec_ctx_get_output(&ctx);
	rc = apei_exec_run(&ctx, ACPI_ERST_GET_ERROR_ATTRIBUTES);
	if (rc)
		return rc;
	range->attr = apei_exec_ctx_get_output(&ctx);

	return 0;
}
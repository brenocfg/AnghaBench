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
typedef  union acpi_object {int dummy; } acpi_object ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  acpi_object_type ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 union acpi_object* acpi_evaluate_dsm_typed (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,union acpi_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_ppi_guid ; 

__attribute__((used)) static inline union acpi_object *
tpm_eval_dsm(acpi_handle ppi_handle, int func, acpi_object_type type,
	     union acpi_object *argv4, u64 rev)
{
	BUG_ON(!ppi_handle);
	return acpi_evaluate_dsm_typed(ppi_handle, &tpm_ppi_guid,
				       rev, func, argv4, type);
}
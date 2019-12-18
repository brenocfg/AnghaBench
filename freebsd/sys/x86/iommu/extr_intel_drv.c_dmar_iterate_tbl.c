#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* dmar_iter_t ) (TYPE_2__*,void*) ;
struct TYPE_6__ {int Length; } ;
struct TYPE_8__ {TYPE_1__ Header; } ;
struct TYPE_7__ {scalar_t__ Length; } ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;
typedef  TYPE_3__ ACPI_TABLE_DMAR ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_DMAR_HEADER ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SIG_DMAR ; 
 int /*<<< orphan*/  AcpiGetTable (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  AcpiPutTable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 

__attribute__((used)) static void
dmar_iterate_tbl(dmar_iter_t iter, void *arg)
{
	ACPI_TABLE_DMAR *dmartbl;
	ACPI_DMAR_HEADER *dmarh;
	char *ptr, *ptrend;
	ACPI_STATUS status;

	status = AcpiGetTable(ACPI_SIG_DMAR, 1, (ACPI_TABLE_HEADER **)&dmartbl);
	if (ACPI_FAILURE(status))
		return;
	ptr = (char *)dmartbl + sizeof(*dmartbl);
	ptrend = (char *)dmartbl + dmartbl->Header.Length;
	for (;;) {
		if (ptr >= ptrend)
			break;
		dmarh = (ACPI_DMAR_HEADER *)ptr;
		if (dmarh->Length <= 0) {
			printf("dmar_identify: corrupted DMAR table, l %d\n",
			    dmarh->Length);
			break;
		}
		ptr += dmarh->Length;
		if (!iter(dmarh, arg))
			break;
	}
	AcpiPutTable((ACPI_TABLE_HEADER *)dmartbl);
}
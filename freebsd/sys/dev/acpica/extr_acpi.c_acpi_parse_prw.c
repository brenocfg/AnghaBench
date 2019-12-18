#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct acpi_prw_data {int power_res_count; TYPE_3__* power_res; int /*<<< orphan*/  gpe_bit; int /*<<< orphan*/ * gpe_handle; int /*<<< orphan*/  lowest_wake; } ;
struct TYPE_12__ {int /*<<< orphan*/ * Pointer; int /*<<< orphan*/  Length; } ;
struct TYPE_10__ {int Count; TYPE_3__* Elements; } ;
struct TYPE_9__ {int /*<<< orphan*/  Value; } ;
struct TYPE_11__ {int Type; TYPE_2__ Package; TYPE_1__ Integer; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_OBJECT ;
typedef  int /*<<< orphan*/ * ACPI_HANDLE ;
typedef  TYPE_4__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_PKG_VALID (TYPE_3__*,int) ; 
 int ACPI_PRW_MAX_POWERRES ; 
#define  ACPI_TYPE_INTEGER 129 
#define  ACPI_TYPE_PACKAGE 128 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiOsFree (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/ * acpi_GetReference (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ acpi_PkgInt32 (TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 char* acpi_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

int
acpi_parse_prw(ACPI_HANDLE h, struct acpi_prw_data *prw)
{
    ACPI_STATUS			status;
    ACPI_BUFFER			prw_buffer;
    ACPI_OBJECT			*res, *res2;
    int				error, i, power_count;

    if (h == NULL || prw == NULL)
	return (EINVAL);

    /*
     * The _PRW object (7.2.9) is only required for devices that have the
     * ability to wake the system from a sleeping state.
     */
    error = EINVAL;
    prw_buffer.Pointer = NULL;
    prw_buffer.Length = ACPI_ALLOCATE_BUFFER;
    status = AcpiEvaluateObject(h, "_PRW", NULL, &prw_buffer);
    if (ACPI_FAILURE(status))
	return (ENOENT);
    res = (ACPI_OBJECT *)prw_buffer.Pointer;
    if (res == NULL)
	return (ENOENT);
    if (!ACPI_PKG_VALID(res, 2))
	goto out;

    /*
     * Element 1 of the _PRW object:
     * The lowest power system sleeping state that can be entered while still
     * providing wake functionality.  The sleeping state being entered must
     * be less than (i.e., higher power) or equal to this value.
     */
    if (acpi_PkgInt32(res, 1, &prw->lowest_wake) != 0)
	goto out;

    /*
     * Element 0 of the _PRW object:
     */
    switch (res->Package.Elements[0].Type) {
    case ACPI_TYPE_INTEGER:
	/*
	 * If the data type of this package element is numeric, then this
	 * _PRW package element is the bit index in the GPEx_EN, in the
	 * GPE blocks described in the FADT, of the enable bit that is
	 * enabled for the wake event.
	 */
	prw->gpe_handle = NULL;
	prw->gpe_bit = res->Package.Elements[0].Integer.Value;
	error = 0;
	break;
    case ACPI_TYPE_PACKAGE:
	/*
	 * If the data type of this package element is a package, then this
	 * _PRW package element is itself a package containing two
	 * elements.  The first is an object reference to the GPE Block
	 * device that contains the GPE that will be triggered by the wake
	 * event.  The second element is numeric and it contains the bit
	 * index in the GPEx_EN, in the GPE Block referenced by the
	 * first element in the package, of the enable bit that is enabled for
	 * the wake event.
	 *
	 * For example, if this field is a package then it is of the form:
	 * Package() {\_SB.PCI0.ISA.GPE, 2}
	 */
	res2 = &res->Package.Elements[0];
	if (!ACPI_PKG_VALID(res2, 2))
	    goto out;
	prw->gpe_handle = acpi_GetReference(NULL, &res2->Package.Elements[0]);
	if (prw->gpe_handle == NULL)
	    goto out;
	if (acpi_PkgInt32(res2, 1, &prw->gpe_bit) != 0)
	    goto out;
	error = 0;
	break;
    default:
	goto out;
    }

    /* Elements 2 to N of the _PRW object are power resources. */
    power_count = res->Package.Count - 2;
    if (power_count > ACPI_PRW_MAX_POWERRES) {
	printf("ACPI device %s has too many power resources\n", acpi_name(h));
	power_count = 0;
    }
    prw->power_res_count = power_count;
    for (i = 0; i < power_count; i++)
	prw->power_res[i] = res->Package.Elements[i];

out:
    if (prw_buffer.Pointer != NULL)
	AcpiOsFree(prw_buffer.Pointer);
    return (error);
}
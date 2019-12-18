#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct acpi_ec_params {int gpe_bit; scalar_t__ glk; int /*<<< orphan*/ * gpe_handle; scalar_t__ uid; } ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  desc ;
struct TYPE_11__ {int /*<<< orphan*/ * Pointer; int /*<<< orphan*/  Length; } ;
struct TYPE_9__ {int /*<<< orphan*/ * Elements; } ;
struct TYPE_8__ {int Value; } ;
struct TYPE_10__ {int Type; TYPE_2__ Package; TYPE_1__ Integer; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;
typedef  TYPE_4__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ACPI_ID_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACPI_PKG_VALID (TYPE_3__*,int) ; 
 scalar_t__ ACPI_TYPE_DEVICE ; 
#define  ACPI_TYPE_INTEGER 129 
#define  ACPI_TYPE_PACKAGE 128 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int AcpiFormatException (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsFree (int /*<<< orphan*/ *) ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  acpi_GetInteger (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/ * acpi_GetReference (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_PkgInt32 (TYPE_3__*,int,int*) ; 
 scalar_t__ acpi_disabled (char*) ; 
 int /*<<< orphan*/  acpi_ec_devclass ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ *) ; 
 struct acpi_ec_params* acpi_get_private (int /*<<< orphan*/ *) ; 
 scalar_t__ acpi_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_set_private (int /*<<< orphan*/ *,struct acpi_ec_params*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  device_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ *) ; 
 scalar_t__ device_is_alive (int /*<<< orphan*/ *) ; 
 scalar_t__ device_is_devclass_fixed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (struct acpi_ec_params*,int /*<<< orphan*/ ) ; 
 struct acpi_ec_params* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char*,char*) ; 

__attribute__((used)) static int
acpi_ec_probe(device_t dev)
{
    ACPI_BUFFER buf;
    ACPI_HANDLE h;
    ACPI_OBJECT *obj;
    ACPI_STATUS status;
    device_t	peer;
    char	desc[64];
    int		ecdt;
    int		ret;
    struct acpi_ec_params *params;
    static char *ec_ids[] = { "PNP0C09", NULL };

    ret = ENXIO;

    /* Check that this is a device and that EC is not disabled. */
    if (acpi_get_type(dev) != ACPI_TYPE_DEVICE || acpi_disabled("ec"))
	return (ret);

    if (device_is_devclass_fixed(dev)) {
	/*
	 * If probed via ECDT, set description and continue. Otherwise, we can
	 * access the namespace and make sure this is not a duplicate probe.
	 */
        ecdt = 1;
        params = acpi_get_private(dev);
	if (params != NULL)
	    ret = 0;

	goto out;
    } else
	ecdt = 0;

    ret = ACPI_ID_PROBE(device_get_parent(dev), dev, ec_ids, NULL);
    if (ret > 0)
	return (ret);

    params = malloc(sizeof(struct acpi_ec_params), M_TEMP, M_WAITOK | M_ZERO);

    buf.Pointer = NULL;
    buf.Length = ACPI_ALLOCATE_BUFFER;
    h = acpi_get_handle(dev);

    /*
     * Read the unit ID to check for duplicate attach and the global lock value
     * to see if we should acquire it when accessing the EC.
     */
    status = acpi_GetInteger(h, "_UID", &params->uid);
    if (ACPI_FAILURE(status))
	params->uid = 0;

    /*
     * Check for a duplicate probe. This can happen when a probe via ECDT
     * succeeded already. If this is a duplicate, disable this device.
     *
     * NB: It would seem device_disable would be sufficient to not get
     * duplicated devices, and ENXIO isn't needed, however, device_probe() only
     * checks DF_ENABLED at the start and so disabling it here is too late to
     * prevent device_attach() from being called.
     */
    peer = devclass_get_device(acpi_ec_devclass, params->uid);
    if (peer != NULL && device_is_alive(peer)) {
	device_disable(dev);
	ret = ENXIO;
	goto out;
    }

    status = acpi_GetInteger(h, "_GLK", &params->glk);
    if (ACPI_FAILURE(status))
	params->glk = 0;

    /*
     * Evaluate the _GPE method to find the GPE bit used by the EC to signal
     * status (SCI).  If it's a package, it contains a reference and GPE bit,
     * similar to _PRW.
     */
    status = AcpiEvaluateObject(h, "_GPE", NULL, &buf);
    if (ACPI_FAILURE(status)) {
	device_printf(dev, "can't evaluate _GPE - %s\n", AcpiFormatException(status));
	goto out;
    }

    obj = (ACPI_OBJECT *)buf.Pointer;
    if (obj == NULL)
	goto out;

    switch (obj->Type) {
    case ACPI_TYPE_INTEGER:
	params->gpe_handle = NULL;
	params->gpe_bit = obj->Integer.Value;
	break;
    case ACPI_TYPE_PACKAGE:
	if (!ACPI_PKG_VALID(obj, 2))
	    goto out;
	params->gpe_handle = acpi_GetReference(NULL, &obj->Package.Elements[0]);
	if (params->gpe_handle == NULL ||
	    acpi_PkgInt32(obj, 1, &params->gpe_bit) != 0)
		goto out;
	break;
    default:
	device_printf(dev, "_GPE has invalid type %d\n", obj->Type);
	goto out;
    }

    /* Store the values we got from the namespace for attach. */
    acpi_set_private(dev, params);

    if (buf.Pointer)
	AcpiOsFree(buf.Pointer);
out:
    if (ret <= 0) {
	snprintf(desc, sizeof(desc), "Embedded Controller: GPE %#x%s%s",
		 params->gpe_bit, (params->glk) ? ", GLK" : "",
		 ecdt ? ", ECDT" : "");
	device_set_desc_copy(dev, desc);
    } else
	free(params, M_TEMP);

    return (ret);
}
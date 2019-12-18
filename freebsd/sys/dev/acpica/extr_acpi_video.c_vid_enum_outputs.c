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
struct enum_callback_arg {int count; void (* callback ) (int /*<<< orphan*/ ,UINT32,void*) ;TYPE_2__* dod_pkg; void* context; } ;
struct TYPE_8__ {int /*<<< orphan*/ * Pointer; int /*<<< orphan*/  Length; } ;
struct TYPE_6__ {int Count; } ;
struct TYPE_7__ {TYPE_1__ Package; } ;
typedef  scalar_t__ ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;
typedef  TYPE_3__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_PKG_VALID (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_DEVICE ; 
 scalar_t__ AE_NOT_FOUND ; 
 scalar_t__ AcpiEvaluateObject (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 char* AcpiFormatException (scalar_t__) ; 
 int /*<<< orphan*/  AcpiOsFree (int /*<<< orphan*/ *) ; 
 scalar_t__ AcpiWalkNamespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct enum_callback_arg*,int /*<<< orphan*/ *) ; 
 char* acpi_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  vid_enum_outputs_subr ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int
vid_enum_outputs(ACPI_HANDLE handle,
		 void (*callback)(ACPI_HANDLE, UINT32, void *), void *context)
{
	ACPI_STATUS status;
	ACPI_BUFFER dod_buf;
	ACPI_OBJECT *res;
	struct enum_callback_arg argset;

	ACPI_SERIAL_ASSERT(video);
	dod_buf.Length = ACPI_ALLOCATE_BUFFER;
	dod_buf.Pointer = NULL;
	status = AcpiEvaluateObject(handle, "_DOD", NULL, &dod_buf);
	if (ACPI_FAILURE(status)) {
		if (status != AE_NOT_FOUND)
			printf("can't evaluate %s._DOD - %s\n",
			       acpi_name(handle), AcpiFormatException(status));
		argset.count = -1;
		goto out;
	}
	res = (ACPI_OBJECT *)dod_buf.Pointer;
	if (!ACPI_PKG_VALID(res, 1)) {
		printf("evaluation of %s._DOD makes no sense\n",
		       acpi_name(handle));
		argset.count = -1;
		goto out;
	}
	if (callback == NULL) {
		argset.count = res->Package.Count;
		goto out;
	}
	argset.callback = callback;
	argset.context  = context;
	argset.dod_pkg  = res;
	argset.count    = 0;
	status = AcpiWalkNamespace(ACPI_TYPE_DEVICE, handle, 1,
	    vid_enum_outputs_subr, NULL, &argset, NULL);
	if (ACPI_FAILURE(status))
		printf("failed walking down %s - %s\n",
		       acpi_name(handle), AcpiFormatException(status));
out:
	if (dod_buf.Pointer != NULL)
		AcpiOsFree(dod_buf.Pointer);
	return (argset.count);
}
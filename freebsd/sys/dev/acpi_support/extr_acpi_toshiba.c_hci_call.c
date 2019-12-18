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
typedef  int UINT32 ;
struct TYPE_12__ {int /*<<< orphan*/ * Pointer; int /*<<< orphan*/  Length; } ;
struct TYPE_9__ {int Value; } ;
struct TYPE_11__ {TYPE_1__ Integer; int /*<<< orphan*/  Type; } ;
struct TYPE_10__ {int Count; TYPE_3__* Pointer; } ;
typedef  TYPE_2__ ACPI_OBJECT_LIST ;
typedef  TYPE_3__ ACPI_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;
typedef  TYPE_4__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_PKG_VALID (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiOsFree (int /*<<< orphan*/ *) ; 
 int ENXIO ; 
 int HCI_GET ; 
 int HCI_NOT_SUPPORTED ; 
 size_t HCI_REG_AX ; 
 size_t HCI_REG_BX ; 
 size_t HCI_REG_CX ; 
 int HCI_REG_SYSTEM_EVENT ; 
 int HCI_SET ; 
 int HCI_SUCCESS ; 
 int HCI_WORDS ; 
 int /*<<< orphan*/  METHOD_HCI ; 
 int /*<<< orphan*/  acpi_PkgInt32 (TYPE_3__*,size_t,int*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  toshiba ; 

__attribute__((used)) static int
hci_call(ACPI_HANDLE h, int op, int function, UINT32 *arg)
{
	ACPI_OBJECT_LIST args;
	ACPI_BUFFER	results;
	ACPI_OBJECT	obj[HCI_WORDS];
	ACPI_OBJECT	*res;
	int		status, i, ret;

	ACPI_SERIAL_ASSERT(toshiba);
	status = ENXIO;

	for (i = 0; i < HCI_WORDS; i++) {
		obj[i].Type = ACPI_TYPE_INTEGER;
		obj[i].Integer.Value = 0;
	}
	obj[HCI_REG_AX].Integer.Value = op;
	obj[HCI_REG_BX].Integer.Value = function;
	if (op == HCI_SET)
		obj[HCI_REG_CX].Integer.Value = *arg;

	args.Count = HCI_WORDS;
	args.Pointer = obj;
	results.Pointer = NULL;
	results.Length = ACPI_ALLOCATE_BUFFER;
	if (ACPI_FAILURE(AcpiEvaluateObject(h, METHOD_HCI, &args, &results)))
		goto end;
	res = (ACPI_OBJECT *)results.Pointer;
	if (!ACPI_PKG_VALID(res, HCI_WORDS)) {
		printf("toshiba: invalid package!\n");
		return (ENXIO);
	}

	acpi_PkgInt32(res, HCI_REG_AX, &ret);
	if (ret == HCI_SUCCESS) {
		if (op == HCI_GET)
			acpi_PkgInt32(res, HCI_REG_CX, arg);
		status = 0;
	} else if (function == HCI_REG_SYSTEM_EVENT && op == HCI_GET &&
	    ret == HCI_NOT_SUPPORTED) {
		/*
		 * Sometimes system events are disabled without us requesting
		 * it.  This workaround attempts to re-enable them.
		 *
		 * XXX This call probably shouldn't be recursive.  Queueing
		 * a task via AcpiOsQueueForExecution() might be better.
		 */
		 i = 1;
		 hci_call(h, HCI_SET, HCI_REG_SYSTEM_EVENT, &i);
	}

end:
	if (results.Pointer != NULL)
		AcpiOsFree(results.Pointer);

	return (status);
}
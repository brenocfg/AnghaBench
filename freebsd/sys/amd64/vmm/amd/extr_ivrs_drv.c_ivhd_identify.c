#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_9__ {int /*<<< orphan*/  Header; } ;
struct TYPE_7__ {scalar_t__ Length; } ;
struct TYPE_8__ {int /*<<< orphan*/  Info; TYPE_1__ Header; } ;
typedef  TYPE_2__ ACPI_TABLE_IVRS ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_IVRS_HARDWARE ;

/* Variables and functions */
 scalar_t__ ACPI_DEV_BASE_ORDER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SIG_IVRS ; 
 int /*<<< orphan*/  AcpiGetTable (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ ,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  KASSERT (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int REG_BITS (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ acpi_disabled (char*) ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ ,char*,int) ; 
 int ivhd_count ; 
 int /*<<< orphan*/  ivhd_count_iter ; 
 int /*<<< orphan*/ ** ivhd_devs ; 
 TYPE_3__* ivhd_find_by_index (int) ; 
 TYPE_3__** ivhd_hdrs ; 
 scalar_t__ ivhd_is_newer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivrs_hdr_iterate_tbl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void
ivhd_identify(driver_t *driver, device_t parent)
{
	ACPI_TABLE_IVRS *ivrs;
	ACPI_IVRS_HARDWARE *ivhd;
	ACPI_STATUS status;
	int i, count = 0;
	uint32_t ivrs_ivinfo;

	if (acpi_disabled("ivhd"))
		return;

	status = AcpiGetTable(ACPI_SIG_IVRS, 1, (ACPI_TABLE_HEADER **)&ivrs);
	if (ACPI_FAILURE(status))
		return;

	if (ivrs->Header.Length == 0) {
		return;
	}

	ivrs_ivinfo = ivrs->Info;
	printf("AMD-Vi: IVRS Info VAsize = %d PAsize = %d GVAsize = %d"
	       " flags:%b\n",
		REG_BITS(ivrs_ivinfo, 21, 15), REG_BITS(ivrs_ivinfo, 14, 8), 
		REG_BITS(ivrs_ivinfo, 7, 5), REG_BITS(ivrs_ivinfo, 22, 22),
		"\020\001EFRSup");

	ivrs_hdr_iterate_tbl(ivhd_count_iter, NULL);
	if (!ivhd_count)
		return;

	for (i = 0; i < ivhd_count; i++) {
		ivhd = ivhd_find_by_index(i);
		KASSERT(ivhd, ("ivhd%d is NULL\n", i));
		ivhd_hdrs[i] = ivhd;
	}

        /* 
	 * Scan for presence of legacy and non-legacy device type
	 * for same AMD-Vi device and override the old one.
	 */
	for (i = ivhd_count - 1 ; i > 0 ; i--){
       		if (ivhd_is_newer(&ivhd_hdrs[i-1]->Header, 
			&ivhd_hdrs[i]->Header)) {
			ivhd_hdrs[i-1] = ivhd_hdrs[i];
			ivhd_count--;
		}
       }	       

	ivhd_devs = malloc(sizeof(device_t) * ivhd_count, M_DEVBUF,
		M_WAITOK | M_ZERO);
	for (i = 0; i < ivhd_count; i++) {
		ivhd = ivhd_hdrs[i];
		KASSERT(ivhd, ("ivhd%d is NULL\n", i));

		/*
		 * Use a high order to ensure that this driver is probed after
		 * the Host-PCI bridge and the root PCI bus.
		 */
		ivhd_devs[i] = BUS_ADD_CHILD(parent,
		    ACPI_DEV_BASE_ORDER + 10 * 10, "ivhd", i);

		/*
		 * XXX: In case device was not destroyed before, add will fail.
		 * locate the old device instance.
		 */
		if (ivhd_devs[i] == NULL) {
			ivhd_devs[i] = device_find_child(parent, "ivhd", i);
			if (ivhd_devs[i] == NULL) {
				printf("AMD-Vi: cant find ivhd%d\n", i);
				break;
			}
		}
		count++;
	}

	/*
	 * Update device count in case failed to attach.
	 */
	ivhd_count = count;
}
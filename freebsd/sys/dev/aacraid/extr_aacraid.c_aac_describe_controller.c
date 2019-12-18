#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct aac_supplement_adapter_info {int /*<<< orphan*/  SupportedOptions2; int /*<<< orphan*/  FeatureBits; scalar_t__ AdapterTypeText; } ;
struct TYPE_4__ {int /*<<< orphan*/  dash; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct TYPE_5__ {TYPE_1__ comp; } ;
struct TYPE_6__ {int /*<<< orphan*/  buildNumber; TYPE_2__ external; } ;
struct aac_softc {int supported_options; int /*<<< orphan*/  aac_io_lock; int /*<<< orphan*/  aac_dev; TYPE_3__ aac_revision; int /*<<< orphan*/  aac_support_opt2; int /*<<< orphan*/  aac_feature_bits; } ;
struct aac_fib {scalar_t__* data; } ;
struct aac_adapter_info {int TotalMem; int BufferMem; int ExecutionMem; int SerialNumber; TYPE_3__ KernelRevision; int /*<<< orphan*/  batteryPlatform; int /*<<< orphan*/  ClockSpeed; int /*<<< orphan*/  CpuVariant; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_DRIVER_BUGFIX_LEVEL ; 
 int /*<<< orphan*/  AAC_DRIVER_BUILD ; 
 int /*<<< orphan*/  AAC_DRIVER_MAJOR_VERSION ; 
 int /*<<< orphan*/  AAC_DRIVER_MINOR_VERSION ; 
 int AAC_SUPPORTED_SUPPLEMENT_ADAPTER_INFO ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  RequestAdapterInfo ; 
 int /*<<< orphan*/  RequestSupplementAdapterInfo ; 
 int /*<<< orphan*/  aac_alloc_sync_fib (struct aac_softc*,struct aac_fib**) ; 
 int /*<<< orphan*/  aac_battery_platform ; 
 int /*<<< orphan*/  aac_cpu_variant ; 
 int /*<<< orphan*/  aac_describe_code (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aac_release_sync_fib (struct aac_softc*) ; 
 scalar_t__ aac_sync_fib (struct aac_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aac_fib*,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
aac_describe_controller(struct aac_softc *sc)
{
	struct aac_fib *fib;
	struct aac_adapter_info	*info;
	char *adapter_type = "Adaptec RAID controller";

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	mtx_lock(&sc->aac_io_lock);
	aac_alloc_sync_fib(sc, &fib);

	if (sc->supported_options & AAC_SUPPORTED_SUPPLEMENT_ADAPTER_INFO) {
		fib->data[0] = 0;
		if (aac_sync_fib(sc, RequestSupplementAdapterInfo, 0, fib, 1)) 
			device_printf(sc->aac_dev, "RequestSupplementAdapterInfo failed\n");
		else {
			struct aac_supplement_adapter_info *supp_info;

			supp_info = ((struct aac_supplement_adapter_info *)&fib->data[0]); 
			adapter_type = (char *)supp_info->AdapterTypeText;
			sc->aac_feature_bits = supp_info->FeatureBits;
			sc->aac_support_opt2 = supp_info->SupportedOptions2;
		}
	}
	device_printf(sc->aac_dev, "%s, aacraid driver %d.%d.%d-%d\n",
		adapter_type,
		AAC_DRIVER_MAJOR_VERSION, AAC_DRIVER_MINOR_VERSION,
		AAC_DRIVER_BUGFIX_LEVEL, AAC_DRIVER_BUILD);

	fib->data[0] = 0;
	if (aac_sync_fib(sc, RequestAdapterInfo, 0, fib, 1)) {
		device_printf(sc->aac_dev, "RequestAdapterInfo failed\n");
		aac_release_sync_fib(sc);
		mtx_unlock(&sc->aac_io_lock);
		return;
	}

	/* save the kernel revision structure for later use */
	info = (struct aac_adapter_info *)&fib->data[0];
	sc->aac_revision = info->KernelRevision;

	if (bootverbose) {
		device_printf(sc->aac_dev, "%s %dMHz, %dMB memory "
		    "(%dMB cache, %dMB execution), %s\n",
		    aac_describe_code(aac_cpu_variant, info->CpuVariant),
		    info->ClockSpeed, info->TotalMem / (1024 * 1024),
		    info->BufferMem / (1024 * 1024),
		    info->ExecutionMem / (1024 * 1024),
		    aac_describe_code(aac_battery_platform,
		    info->batteryPlatform));

		device_printf(sc->aac_dev,
		    "Kernel %d.%d-%d, Build %d, S/N %6X\n",
		    info->KernelRevision.external.comp.major,
		    info->KernelRevision.external.comp.minor,
		    info->KernelRevision.external.comp.dash,
		    info->KernelRevision.buildNumber,
		    (u_int32_t)(info->SerialNumber & 0xffffff));

		device_printf(sc->aac_dev, "Supported Options=%b\n",
			      sc->supported_options,
			      "\20"
			      "\1SNAPSHOT"
			      "\2CLUSTERS"
			      "\3WCACHE"
			      "\4DATA64"
			      "\5HOSTTIME"
			      "\6RAID50"
			      "\7WINDOW4GB"
			      "\10SCSIUPGD"
			      "\11SOFTERR"
			      "\12NORECOND"
			      "\13SGMAP64"
			      "\14ALARM"
			      "\15NONDASD"
			      "\16SCSIMGT"
			      "\17RAIDSCSI"
			      "\21ADPTINFO"
			      "\22NEWCOMM"
			      "\23ARRAY64BIT"
			      "\24HEATSENSOR");
	}

	aac_release_sync_fib(sc);
	mtx_unlock(&sc->aac_io_lock);
}
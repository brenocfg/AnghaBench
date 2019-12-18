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
typedef  int u_short ;
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  BIOS_RESET ; 
 int /*<<< orphan*/  BIOS_WARM ; 
 int /*<<< orphan*/  CHECK_INIT (int) ; 
 int /*<<< orphan*/  CHECK_PRINT (char*) ; 
 int /*<<< orphan*/  CMOS_DATA ; 
 int /*<<< orphan*/  CMOS_REG ; 
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int DPCPU_SIZE ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TRAMP_COPYOUT_SZ ; 
 int /*<<< orphan*/  TRAMP_STACK_SZ ; 
 scalar_t__ WARMBOOT_OFF ; 
 scalar_t__ WARMBOOT_SEG ; 
 int WARMBOOT_TARGET ; 
 int /*<<< orphan*/  all_cpus ; 
 int /*<<< orphan*/  ap_boot_mtx ; 
 void* ap_copyout_buf ; 
 void* ap_tramp_stack_base ; 
 int bootAP ; 
 char* bootSTK ; 
 int boot_address ; 
 char** bootstacks ; 
 char cngetc () ; 
 int* cpu_apic_ids ; 
 void* dpcpu ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  install_ap_tramp () ; 
 scalar_t__ kmem_malloc (int,int) ; 
 int kstack_pages ; 
 int mp_naps ; 
 int mp_ncpus ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pmap_remap_lower (int) ; 
 void* pmap_trm_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  start_ap (int) ; 

__attribute__((used)) static int
start_all_aps(void)
{
	u_char mpbiosreason;
	u_int32_t mpbioswarmvec;
	int apic_id, cpu;

	mtx_init(&ap_boot_mtx, "ap boot", NULL, MTX_SPIN);

	pmap_remap_lower(true);

	/* install the AP 1st level boot code */
	install_ap_tramp();

	/* save the current value of the warm-start vector */
	mpbioswarmvec = *((u_int32_t *) WARMBOOT_OFF);
	outb(CMOS_REG, BIOS_RESET);
	mpbiosreason = inb(CMOS_DATA);

	/* take advantage of the P==V mapping for PTD[0] for AP boot */

	/* start each AP */
	for (cpu = 1; cpu < mp_ncpus; cpu++) {
		apic_id = cpu_apic_ids[cpu];

		/* allocate and set up a boot stack data page */
		bootstacks[cpu] = (char *)kmem_malloc(kstack_pages * PAGE_SIZE,
		    M_WAITOK | M_ZERO);
		dpcpu = (void *)kmem_malloc(DPCPU_SIZE, M_WAITOK | M_ZERO);
		/* setup a vector to our boot code */
		*((volatile u_short *) WARMBOOT_OFF) = WARMBOOT_TARGET;
		*((volatile u_short *) WARMBOOT_SEG) = (boot_address >> 4);
		outb(CMOS_REG, BIOS_RESET);
		outb(CMOS_DATA, BIOS_WARM);	/* 'warm-start' */

		bootSTK = (char *)bootstacks[cpu] + kstack_pages *
		    PAGE_SIZE - 4;
		bootAP = cpu;

		ap_tramp_stack_base = pmap_trm_alloc(TRAMP_STACK_SZ, M_NOWAIT);
		ap_copyout_buf = pmap_trm_alloc(TRAMP_COPYOUT_SZ, M_NOWAIT);

		/* attempt to start the Application Processor */
		CHECK_INIT(99);	/* setup checkpoints */
		if (!start_ap(apic_id)) {
			printf("AP #%d (PHY# %d) failed!\n", cpu, apic_id);
			CHECK_PRINT("trace");	/* show checkpoints */
			/* better panic as the AP may be running loose */
			printf("panic y/n? [y] ");
			if (cngetc() != 'n')
				panic("bye-bye");
		}
		CHECK_PRINT("trace");		/* show checkpoints */

		CPU_SET(cpu, &all_cpus);	/* record AP in CPU map */
	}

	pmap_remap_lower(false);

	/* restore the warmstart vector */
	*(u_int32_t *) WARMBOOT_OFF = mpbioswarmvec;

	outb(CMOS_REG, BIOS_RESET);
	outb(CMOS_DATA, mpbiosreason);

	/* number of APs actually started */
	return mp_naps;
}
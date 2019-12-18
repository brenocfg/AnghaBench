#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  int u_int ;
struct vm86frame {int dummy; } ;
struct TYPE_4__ {int tss_ioopt; int /*<<< orphan*/  tss_ss0; void* tss_esp0; } ;
struct TYPE_3__ {int vm86_has_vme; scalar_t__ vm86_intmap; } ;
struct pcb_ext {int new_ptd; int /*<<< orphan*/  ext_tssd; TYPE_2__ ext_tss; TYPE_1__ ext_vm86; scalar_t__ ext_iomap; struct pcb_ext* pcb_ext; int /*<<< orphan*/  pcb_flags; void* pgtable_va; void* vm86_frame; } ;
struct vm86_layout_nopae {int vml_iomap_trailer; scalar_t__ vml_intmap; scalar_t__ vml_iomap; struct pcb_ext vml_ext; struct pcb_ext vml_pcb; } ;
struct vm86_layout {int dummy; } ;
struct soft_segment_descriptor {int member_4; int ssd_base; scalar_t__ ssd_limit; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct pcb {int new_ptd; int /*<<< orphan*/  ext_tssd; TYPE_2__ ext_tss; TYPE_1__ ext_vm86; scalar_t__ ext_iomap; struct pcb* pcb_ext; int /*<<< orphan*/  pcb_flags; void* pgtable_va; void* vm86_frame; } ;

/* Variables and functions */
 int CPUID_VME ; 
 int CR4_VME ; 
 int /*<<< orphan*/  GDATA_SEL ; 
 int /*<<< orphan*/  GSEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INTMAP_SIZE ; 
 int IOMAP_SIZE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  PCB_VM86CALL ; 
 int PG_RW ; 
 int PG_U ; 
 int PG_V ; 
 int /*<<< orphan*/  SDT_SYS386TSS ; 
 int /*<<< orphan*/  SEL_KPL ; 
 scalar_t__ TSS_SIZE ; 
 int /*<<< orphan*/  bzero (struct pcb_ext*,int) ; 
 int cpu_feature ; 
 scalar_t__ ctob (int) ; 
 int /*<<< orphan*/  msgbufinit (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rcr4 () ; 
 int /*<<< orphan*/  ssdtosd (struct soft_segment_descriptor*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm86_lock ; 
 int vm86pa ; 
 void* vm86paddr ; 
 struct pcb_ext* vm86pcb ; 

__attribute__((used)) static void
vm86_initialize_nopae(void)
{
	int i;
	u_int *addr;
	struct vm86_layout_nopae *vml;
	struct pcb *pcb;
	struct pcb_ext *ext;
	struct soft_segment_descriptor ssd = {
		0,			/* segment base address (overwritten) */
		0,			/* length (overwritten) */
		SDT_SYS386TSS,		/* segment type */
		0,			/* priority level */
		1,			/* descriptor present */
		0, 0,
		0,			/* default 16 size */
		0			/* granularity */
	};

	vml = (struct vm86_layout_nopae *)vm86paddr;
	pcb = &vml->vml_pcb;
	ext = &vml->vml_ext;

	mtx_init(&vm86_lock, "vm86 lock", NULL, MTX_DEF);

	bzero(pcb, sizeof(struct pcb));
	pcb->new_ptd = vm86pa | PG_V | PG_RW | PG_U;
	pcb->vm86_frame = vm86paddr - sizeof(struct vm86frame);
	pcb->pgtable_va = vm86paddr;
	pcb->pcb_flags = PCB_VM86CALL;
	pcb->pcb_ext = ext;

	bzero(ext, sizeof(struct pcb_ext));
	ext->ext_tss.tss_esp0 = vm86paddr;
	ext->ext_tss.tss_ss0 = GSEL(GDATA_SEL, SEL_KPL);
	ext->ext_tss.tss_ioopt =
		((u_int)vml->vml_iomap - (u_int)&ext->ext_tss) << 16;
	ext->ext_iomap = vml->vml_iomap;
	ext->ext_vm86.vm86_intmap = vml->vml_intmap;

	if (cpu_feature & CPUID_VME)
		ext->ext_vm86.vm86_has_vme = (rcr4() & CR4_VME ? 1 : 0);

	addr = (u_int *)ext->ext_vm86.vm86_intmap;
	for (i = 0; i < (INTMAP_SIZE + IOMAP_SIZE) / sizeof(u_int); i++)
		*addr++ = 0;
	vml->vml_iomap_trailer = 0xff;

	ssd.ssd_base = (u_int)&ext->ext_tss;
	ssd.ssd_limit = TSS_SIZE - 1;
	ssdtosd(&ssd, &ext->ext_tssd);

	vm86pcb = pcb;

#if 0
        /*
         * use whatever is leftover of the vm86 page layout as a
         * message buffer so we can capture early output.
         */
        msgbufinit((vm_offset_t)vm86paddr + sizeof(struct vm86_layout),
            ctob(3) - sizeof(struct vm86_layout));
#endif
}
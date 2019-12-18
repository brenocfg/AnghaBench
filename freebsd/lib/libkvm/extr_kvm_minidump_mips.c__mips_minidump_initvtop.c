#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_13__ {scalar_t__ version; scalar_t__ msgbufsize; scalar_t__ bitmapsize; scalar_t__ ptesize; void* dmapend; void* dmapbase; void* kernbase; int /*<<< orphan*/  magic; } ;
struct vmstate {int pte_size; TYPE_3__ hdr; } ;
typedef  scalar_t__ off_t ;
struct TYPE_11__ {scalar_t__* e_ident; int e_flags; } ;
struct TYPE_12__ {int /*<<< orphan*/  program; int /*<<< orphan*/  pmfd; TYPE_1__ nlehdr; struct vmstate* vmst; } ;
typedef  TYPE_2__ kvm_t ;

/* Variables and functions */
 int EF_MIPS_ABI2 ; 
 size_t EI_CLASS ; 
 scalar_t__ ELFCLASS64 ; 
 int /*<<< orphan*/  MINIDUMP_MAGIC ; 
 scalar_t__ MINIDUMP_VERSION ; 
 scalar_t__ MIPS_PAGE_SIZE ; 
 void* _kvm32toh (TYPE_2__*,scalar_t__) ; 
 void* _kvm64toh (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  _kvm_err (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 struct vmstate* _kvm_malloc (TYPE_2__*,int) ; 
 int _kvm_pmap_init (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int _kvm_pt_init (TYPE_2__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 scalar_t__ mips_round_page (scalar_t__) ; 
 int pread (int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
_mips_minidump_initvtop(kvm_t *kd)
{
	struct vmstate *vmst;
	off_t off, sparse_off;

	vmst = _kvm_malloc(kd, sizeof(*vmst));
	if (vmst == NULL) {
		_kvm_err(kd, kd->program, "cannot allocate vm");
		return (-1);
	}

	kd->vmst = vmst;

	if (kd->nlehdr.e_ident[EI_CLASS] == ELFCLASS64 ||
	    kd->nlehdr.e_flags & EF_MIPS_ABI2)
		vmst->pte_size = 64;
	else
		vmst->pte_size = 32;

	if (pread(kd->pmfd, &vmst->hdr,
	    sizeof(vmst->hdr), 0) != sizeof(vmst->hdr)) {
		_kvm_err(kd, kd->program, "cannot read dump header");
		return (-1);
	}

	if (strncmp(MINIDUMP_MAGIC, vmst->hdr.magic,
	    sizeof(vmst->hdr.magic)) != 0) {
		_kvm_err(kd, kd->program, "not a minidump for this platform");
		return (-1);
	}
	vmst->hdr.version = _kvm32toh(kd, vmst->hdr.version);
	if (vmst->hdr.version != MINIDUMP_VERSION) {
		_kvm_err(kd, kd->program, "wrong minidump version. "
		    "Expected %d got %d", MINIDUMP_VERSION, vmst->hdr.version);
		return (-1);
	}
	vmst->hdr.msgbufsize = _kvm32toh(kd, vmst->hdr.msgbufsize);
	vmst->hdr.bitmapsize = _kvm32toh(kd, vmst->hdr.bitmapsize);
	vmst->hdr.ptesize = _kvm32toh(kd, vmst->hdr.ptesize);
	vmst->hdr.kernbase = _kvm64toh(kd, vmst->hdr.kernbase);
	vmst->hdr.dmapbase = _kvm64toh(kd, vmst->hdr.dmapbase);
	vmst->hdr.dmapend = _kvm64toh(kd, vmst->hdr.dmapend);

	/* Skip header and msgbuf */
	off = MIPS_PAGE_SIZE + mips_round_page(vmst->hdr.msgbufsize);

	sparse_off = off + mips_round_page(vmst->hdr.bitmapsize) +
	    mips_round_page(vmst->hdr.ptesize);
	if (_kvm_pt_init(kd, vmst->hdr.bitmapsize, off, sparse_off,
	    MIPS_PAGE_SIZE, sizeof(uint32_t)) == -1) {
		return (-1);
	}
	off += mips_round_page(vmst->hdr.bitmapsize);

	if (_kvm_pmap_init(kd, vmst->hdr.ptesize, off) == -1) {
		return (-1);
	}
	off += mips_round_page(vmst->hdr.ptesize);

	return (0);
}
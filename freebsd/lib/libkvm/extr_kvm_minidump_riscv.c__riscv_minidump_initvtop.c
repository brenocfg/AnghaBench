#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_9__ {scalar_t__ version; scalar_t__ msgbufsize; scalar_t__ bitmapsize; scalar_t__ pmapsize; void* dmapend; void* dmapbase; void* dmapphys; void* kernbase; int /*<<< orphan*/  magic; } ;
struct vmstate {TYPE_2__ hdr; } ;
typedef  scalar_t__ off_t ;
struct TYPE_8__ {int /*<<< orphan*/  program; int /*<<< orphan*/  pmfd; struct vmstate* vmst; } ;
typedef  TYPE_1__ kvm_t ;

/* Variables and functions */
 int /*<<< orphan*/  MINIDUMP_MAGIC ; 
 scalar_t__ MINIDUMP_VERSION ; 
 scalar_t__ RISCV_PAGE_SIZE ; 
 int /*<<< orphan*/  _kvm_err (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 struct vmstate* _kvm_malloc (TYPE_1__*,int) ; 
 int _kvm_pmap_init (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int _kvm_pt_init (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 void* le32toh (scalar_t__) ; 
 void* le64toh (void*) ; 
 int pread (int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ riscv_round_page (scalar_t__) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
_riscv_minidump_initvtop(kvm_t *kd)
{
	struct vmstate *vmst;
	off_t off, sparse_off;

	vmst = _kvm_malloc(kd, sizeof(*vmst));
	if (vmst == NULL) {
		_kvm_err(kd, kd->program, "cannot allocate vm");
		return (-1);
	}
	kd->vmst = vmst;
	if (pread(kd->pmfd, &vmst->hdr, sizeof(vmst->hdr), 0) !=
	    sizeof(vmst->hdr)) {
		_kvm_err(kd, kd->program, "cannot read dump header");
		return (-1);
	}
	if (strncmp(MINIDUMP_MAGIC, vmst->hdr.magic,
	    sizeof(vmst->hdr.magic)) != 0) {
		_kvm_err(kd, kd->program, "not a minidump for this platform");
		return (-1);
	}

	vmst->hdr.version = le32toh(vmst->hdr.version);
	if (vmst->hdr.version != MINIDUMP_VERSION) {
		_kvm_err(kd, kd->program, "wrong minidump version. "
		    "Expected %d got %d", MINIDUMP_VERSION, vmst->hdr.version);
		return (-1);
	}
	vmst->hdr.msgbufsize = le32toh(vmst->hdr.msgbufsize);
	vmst->hdr.bitmapsize = le32toh(vmst->hdr.bitmapsize);
	vmst->hdr.pmapsize = le32toh(vmst->hdr.pmapsize);
	vmst->hdr.kernbase = le64toh(vmst->hdr.kernbase);
	vmst->hdr.dmapphys = le64toh(vmst->hdr.dmapphys);
	vmst->hdr.dmapbase = le64toh(vmst->hdr.dmapbase);
	vmst->hdr.dmapend = le64toh(vmst->hdr.dmapend);

	/* Skip header and msgbuf */
	off = RISCV_PAGE_SIZE + riscv_round_page(vmst->hdr.msgbufsize);

	/* build physical address lookup table for sparse pages */
	sparse_off = off + riscv_round_page(vmst->hdr.bitmapsize) +
	    riscv_round_page(vmst->hdr.pmapsize);
	if (_kvm_pt_init(kd, vmst->hdr.bitmapsize, off, sparse_off,
	    RISCV_PAGE_SIZE, sizeof(uint64_t)) == -1) {
		return (-1);
	}
	off += riscv_round_page(vmst->hdr.bitmapsize);

	if (_kvm_pmap_init(kd, vmst->hdr.pmapsize, off) == -1) {
		return (-1);
	}
	off += riscv_round_page(vmst->hdr.pmapsize);

	return (0);
}
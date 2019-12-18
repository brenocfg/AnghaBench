#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct vmstate {char* PTD; int pae; int /*<<< orphan*/  phdr; int /*<<< orphan*/  phnum; } ;
struct kvm_nlist {char* n_name; int n_value; } ;
typedef  int /*<<< orphan*/  pa64 ;
typedef  int /*<<< orphan*/  pa ;
struct TYPE_8__ {scalar_t__ rawdump; struct vmstate* vmst; int /*<<< orphan*/  program; } ;
typedef  TYPE_1__ kvm_t ;
typedef  int kvaddr_t ;
typedef  int i386_physaddr_t ;
typedef  int i386_physaddr_pae_t ;

/* Variables and functions */
 int I386_PAGE_SIZE ; 
 int I386_PG_FRAME_PAE ; 
 int KERNBASE ; 
 int /*<<< orphan*/  _kvm_err (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 char* _kvm_malloc (TYPE_1__*,int) ; 
 int _kvm_read_core_phdrs (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ kvm_nlist2 (TYPE_1__*,struct kvm_nlist*) ; 
 int kvm_read2 (TYPE_1__*,int,...) ; 
 int le32toh (int) ; 
 int le64toh (int) ; 

__attribute__((used)) static int
_i386_initvtop(kvm_t *kd)
{
	struct kvm_nlist nl[2];
	i386_physaddr_t pa;
	kvaddr_t kernbase;
	char		*PTD;
	int		i;

	kd->vmst = (struct vmstate *)_kvm_malloc(kd, sizeof(struct vmstate));
	if (kd->vmst == NULL) {
		_kvm_err(kd, kd->program, "cannot allocate vm");
		return (-1);
	}
	kd->vmst->PTD = 0;

	if (kd->rawdump == 0) {
		if (_kvm_read_core_phdrs(kd, &kd->vmst->phnum,
		    &kd->vmst->phdr) == -1)
			return (-1);
	}

	nl[0].n_name = "kernbase";
	nl[1].n_name = 0;

	if (kvm_nlist2(kd, nl) != 0) {
#ifdef __i386__
		kernbase = KERNBASE;	/* for old kernels */
#else
		_kvm_err(kd, kd->program, "cannot resolve kernbase");
		return (-1);
#endif
	} else
		kernbase = nl[0].n_value;

	nl[0].n_name = "IdlePDPT";
	nl[1].n_name = 0;

	if (kvm_nlist2(kd, nl) == 0) {
		i386_physaddr_pae_t pa64;

		if (kvm_read2(kd, (nl[0].n_value - kernbase), &pa,
		    sizeof(pa)) != sizeof(pa)) {
			_kvm_err(kd, kd->program, "cannot read IdlePDPT");
			return (-1);
		}
		pa = le32toh(pa);
		PTD = _kvm_malloc(kd, 4 * I386_PAGE_SIZE);
		if (PTD == NULL) {
			_kvm_err(kd, kd->program, "cannot allocate PTD");
			return (-1);
		}
		for (i = 0; i < 4; i++) {
			if (kvm_read2(kd, pa + (i * sizeof(pa64)), &pa64,
			    sizeof(pa64)) != sizeof(pa64)) {
				_kvm_err(kd, kd->program, "Cannot read PDPT");
				free(PTD);
				return (-1);
			}
			pa64 = le64toh(pa64);
			if (kvm_read2(kd, pa64 & I386_PG_FRAME_PAE,
			    PTD + (i * I386_PAGE_SIZE), I386_PAGE_SIZE) !=
			    I386_PAGE_SIZE) {
				_kvm_err(kd, kd->program, "cannot read PDPT");
				free(PTD);
				return (-1);
			}
		}
		kd->vmst->PTD = PTD;
		kd->vmst->pae = 1;
	} else {
		nl[0].n_name = "IdlePTD";
		nl[1].n_name = 0;

		if (kvm_nlist2(kd, nl) != 0) {
			_kvm_err(kd, kd->program, "bad namelist");
			return (-1);
		}
		if (kvm_read2(kd, (nl[0].n_value - kernbase), &pa,
		    sizeof(pa)) != sizeof(pa)) {
			_kvm_err(kd, kd->program, "cannot read IdlePTD");
			return (-1);
		}
		pa = le32toh(pa);
		PTD = _kvm_malloc(kd, I386_PAGE_SIZE);
		if (PTD == NULL) {
			_kvm_err(kd, kd->program, "cannot allocate PTD");
			return (-1);
		}
		if (kvm_read2(kd, pa, PTD, I386_PAGE_SIZE) != I386_PAGE_SIZE) {
			_kvm_err(kd, kd->program, "cannot read PTD");
			return (-1);
		}
		kd->vmst->PTD = PTD;
		kd->vmst->pae = 0;
	}
	return (0);
}
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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct vmctx {int dummy; } ;
struct pci_emul_dsoftc {int* ioregs; int** memregs; } ;
struct pci_devinst {struct pci_emul_dsoftc* pi_arg; } ;

/* Variables and functions */
 int DIOSZ ; 
 int DMEMSZ ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static uint64_t
pci_emul_dior(struct vmctx *ctx, int vcpu, struct pci_devinst *pi, int baridx,
	      uint64_t offset, int size)
{
	struct pci_emul_dsoftc *sc = pi->pi_arg;
	uint32_t value;
	int i;

	if (baridx == 0) {
		if (offset + size > DIOSZ) {
			printf("dior: ior too large, offset %ld size %d\n",
			       offset, size);
			return (0);
		}

		value = 0;
		if (size == 1) {
			value = sc->ioregs[offset];
		} else if (size == 2) {
			value = *(uint16_t *) &sc->ioregs[offset];
		} else if (size == 4) {
			value = *(uint32_t *) &sc->ioregs[offset];
		} else {
			printf("dior: ior unknown size %d\n", size);
		}
	}

	if (baridx == 1 || baridx == 2) {
		if (offset + size > DMEMSZ) {
			printf("dior: memr too large, offset %ld size %d\n",
			       offset, size);
			return (0);
		}

		i = baridx - 1;		/* 'memregs' index */

		if (size == 1) {
			value = sc->memregs[i][offset];
		} else if (size == 2) {
			value = *(uint16_t *) &sc->memregs[i][offset];
		} else if (size == 4) {
			value = *(uint32_t *) &sc->memregs[i][offset];
		} else if (size == 8) {
			value = *(uint64_t *) &sc->memregs[i][offset];
		} else {
			printf("dior: ior unknown size %d\n", size);
		}
	}


	if (baridx > 2 || baridx < 0) {
		printf("dior: unknown bar idx %d\n", baridx);
		return (0);
	}

	return (value);
}
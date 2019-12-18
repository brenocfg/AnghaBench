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
struct isa_attach_args {int ia_iosize; int ia_maddr; int /*<<< orphan*/  ia_msize; int /*<<< orphan*/  ia_iobase; int /*<<< orphan*/  ia_iot; int /*<<< orphan*/  ia_memt; } ;
struct cfdata {scalar_t__ cf_unit; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  TPM_SIZE ; 
 scalar_t__ bus_space_map (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tpm_legacy_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tpm_tis12_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
tpm_match(device_t parent, void *match, void *aux)
{
	struct isa_attach_args *ia = aux;
	struct cfdata *cf = match;
	bus_space_tag_t bt = ia->ia_memt;
	bus_space_handle_t bh;
	int rv;

	/* There can be only one. */
	if (cf->cf_unit)
		return 0;

	if (tpm_legacy_probe(ia->ia_iot, ia->ia_iobase)) {
		ia->ia_iosize = 2;
		return 1;
	}

	if (ia->ia_maddr == -1)
		return 0;

	if (bus_space_map(bt, ia->ia_maddr, TPM_SIZE, 0, &bh))
		return 0;

	if ((rv = tpm_tis12_probe(bt, bh))) {
		ia->ia_iosize = 0;
		ia->ia_msize = TPM_SIZE;
	}

	bus_space_unmap(bt, bh, TPM_SIZE);
	return rv;
}
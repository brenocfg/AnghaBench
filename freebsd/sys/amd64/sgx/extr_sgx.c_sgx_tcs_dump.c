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
struct tcs {int /*<<< orphan*/  gslimit; int /*<<< orphan*/  fslimit; int /*<<< orphan*/  ogsbasgx; int /*<<< orphan*/  ofsbasgx; int /*<<< orphan*/  oentry; int /*<<< orphan*/  nssa; int /*<<< orphan*/  cssa; int /*<<< orphan*/  ossa; int /*<<< orphan*/  flags; } ;
struct sgx_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sgx_tcs_dump(struct sgx_softc *sc, struct tcs *t)
{

	dprintf("t->flags %lx\n", t->flags);
	dprintf("t->ossa %lx\n", t->ossa);
	dprintf("t->cssa %x\n", t->cssa);
	dprintf("t->nssa %x\n", t->nssa);
	dprintf("t->oentry %lx\n", t->oentry);
	dprintf("t->ofsbasgx %lx\n", t->ofsbasgx);
	dprintf("t->ogsbasgx %lx\n", t->ogsbasgx);
	dprintf("t->fslimit %x\n", t->fslimit);
	dprintf("t->gslimit %x\n", t->gslimit);
}
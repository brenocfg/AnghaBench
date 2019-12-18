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
struct TYPE_4__ {TYPE_1__* fc; } ;
struct dcons_crom_softc {int /*<<< orphan*/  unit; int /*<<< orphan*/  ver; int /*<<< orphan*/  spec; TYPE_2__ fd; } ;
struct crom_src {int dummy; } ;
struct crom_chunk {int dummy; } ;
struct TYPE_3__ {struct crom_chunk* crom_root; struct crom_src* crom_src; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADDR_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CROM_UDIR ; 
 int /*<<< orphan*/  CSRKEY_SPEC ; 
 int /*<<< orphan*/  CSRKEY_VER ; 
 int /*<<< orphan*/  CSRVAL_VENDOR_PRIVATE ; 
 int /*<<< orphan*/  DCONS_CSR_KEY_HI ; 
 int /*<<< orphan*/  DCONS_CSR_KEY_LO ; 
 int /*<<< orphan*/  DCONS_CSR_VAL_VER ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  crom_add_chunk (struct crom_src*,struct crom_chunk*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crom_add_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crom_add_simple_text (struct crom_src*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dcons_crom_expose_idt (struct dcons_crom_softc*) ; 
 int /*<<< orphan*/  dcons_paddr ; 

__attribute__((used)) static void
dcons_crom_post_busreset(void *arg)
{
	struct dcons_crom_softc *sc;
	struct crom_src *src;
	struct crom_chunk *root;

	sc = (struct dcons_crom_softc *) arg;
	src = sc->fd.fc->crom_src;
	root = sc->fd.fc->crom_root;

	bzero(&sc->unit, sizeof(struct crom_chunk));

	crom_add_chunk(src, root, &sc->unit, CROM_UDIR);
	crom_add_entry(&sc->unit, CSRKEY_SPEC, CSRVAL_VENDOR_PRIVATE);
	crom_add_simple_text(src, &sc->unit, &sc->spec, "FreeBSD");
	crom_add_entry(&sc->unit, CSRKEY_VER, DCONS_CSR_VAL_VER);
	crom_add_simple_text(src, &sc->unit, &sc->ver, "dcons");
	crom_add_entry(&sc->unit, DCONS_CSR_KEY_HI, ADDR_HI(dcons_paddr));
	crom_add_entry(&sc->unit, DCONS_CSR_KEY_LO, ADDR_LO(dcons_paddr));
#if (defined(__i386__) || defined(__amd64__))
	dcons_crom_expose_idt(sc);
#endif
}
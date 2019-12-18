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
struct fwohci_softc {struct crom_chunk* crom_root; struct crom_src* crom_src; struct crom_src_buf* crom_src_buf; } ;
struct crom_src_buf {int /*<<< orphan*/  vendor; } ;
struct crom_src {int /*<<< orphan*/  chunk_list; } ;
struct crom_chunk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSRKEY_NCAP ; 
 int /*<<< orphan*/  CSRKEY_VENDOR ; 
 int CSRVAL_VENDOR_PRIVATE ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct crom_chunk*,int) ; 
 int /*<<< orphan*/  crom_add_chunk (struct crom_src*,int /*<<< orphan*/ *,struct crom_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crom_add_entry (struct crom_chunk*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  crom_add_simple_text (struct crom_src*,struct crom_chunk*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fw_init_crom (struct fwohci_softc*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
fw_reset_crom(struct fwohci_softc *sc)
{
	struct crom_src_buf *buf;
	struct crom_src *src;
	struct crom_chunk *root;

	printf("fw_reset\n");
	if (sc->crom_src_buf == NULL)
		fw_init_crom(sc);

	buf = sc->crom_src_buf;
	src = sc->crom_src;
	root = sc->crom_root;

	STAILQ_INIT(&src->chunk_list);

	bzero(root, sizeof(struct crom_chunk));
	crom_add_chunk(src, NULL, root, 0);
	crom_add_entry(root, CSRKEY_NCAP, 0x0083c0); /* XXX */
	/* private company_id */
	crom_add_entry(root, CSRKEY_VENDOR, CSRVAL_VENDOR_PRIVATE);
#ifdef __DragonFly__
	crom_add_simple_text(src, root, &buf->vendor, "DragonFly Project");
#else
	crom_add_simple_text(src, root, &buf->vendor, "FreeBSD Project");
#endif
}
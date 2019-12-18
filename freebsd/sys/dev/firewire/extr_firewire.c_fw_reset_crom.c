#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct firewire_comm {struct crom_chunk* crom_root; struct crom_src* crom_src; struct crom_src_buf* crom_src_buf; } ;
struct crom_src_buf {int /*<<< orphan*/  hw; int /*<<< orphan*/  vendor; } ;
struct crom_src {int /*<<< orphan*/  chunk_list; } ;
struct crom_chunk {int dummy; } ;
struct TYPE_2__ {char* pr_hostname; int /*<<< orphan*/  pr_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSRKEY_HW ; 
 int /*<<< orphan*/  CSRKEY_NCAP ; 
 int /*<<< orphan*/  CSRKEY_VENDOR ; 
 int CSRVAL_VENDOR_PRIVATE ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int __FreeBSD_version ; 
 int /*<<< orphan*/  bzero (struct crom_chunk*,int) ; 
 int /*<<< orphan*/  crom_add_chunk (struct crom_src*,int /*<<< orphan*/ *,struct crom_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crom_add_entry (struct crom_chunk*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  crom_add_simple_text (struct crom_src*,struct crom_chunk*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ prison0 ; 

__attribute__((used)) static void
fw_reset_crom(struct firewire_comm *fc)
{
	struct crom_src_buf *buf;
	struct crom_src *src;
	struct crom_chunk *root;

	buf =  fc->crom_src_buf;
	src = fc->crom_src;
	root = fc->crom_root;

	STAILQ_INIT(&src->chunk_list);

	bzero(root, sizeof(struct crom_chunk));
	crom_add_chunk(src, NULL, root, 0);
	crom_add_entry(root, CSRKEY_NCAP, 0x0083c0); /* XXX */
	/* private company_id */
	crom_add_entry(root, CSRKEY_VENDOR, CSRVAL_VENDOR_PRIVATE);
	crom_add_simple_text(src, root, &buf->vendor, "FreeBSD Project");
	crom_add_entry(root, CSRKEY_HW, __FreeBSD_version);
	mtx_lock(&prison0.pr_mtx);
	crom_add_simple_text(src, root, &buf->hw, prison0.pr_hostname);
	mtx_unlock(&prison0.pr_mtx);
}
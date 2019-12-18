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
struct zbuf {int zb_flags; TYPE_1__* zb_header; } ;
struct bpf_d {scalar_t__ bd_bufmode; int /*<<< orphan*/  bd_hlen; scalar_t__ bd_hbuf; } ;
struct TYPE_2__ {int /*<<< orphan*/  bzh_kernel_gen; int /*<<< orphan*/  bzh_kernel_len; } ;

/* Variables and functions */
 scalar_t__ BPF_BUFMODE_ZBUF ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int ZBUF_FLAG_ASSIGNED ; 
 int /*<<< orphan*/  atomic_add_rel_int (int /*<<< orphan*/ *,int) ; 

void
bpf_zerocopy_bufheld(struct bpf_d *d)
{
	struct zbuf *zb;

	KASSERT(d->bd_bufmode == BPF_BUFMODE_ZBUF,
	    ("bpf_zerocopy_bufheld: not in zbuf mode"));

	zb = (struct zbuf *)d->bd_hbuf;
	KASSERT(zb != NULL, ("bpf_zerocopy_bufheld: zb == NULL"));

	if ((zb->zb_flags & ZBUF_FLAG_ASSIGNED) == 0) {
		zb->zb_flags |= ZBUF_FLAG_ASSIGNED;
		zb->zb_header->bzh_kernel_len = d->bd_hlen;
		atomic_add_rel_int(&zb->zb_header->bzh_kernel_gen, 1);
	}
}
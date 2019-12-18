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
struct zbuf {int /*<<< orphan*/  zb_flags; } ;
struct bpf_d {scalar_t__ bd_bufmode; int /*<<< orphan*/ * bd_fbuf; } ;

/* Variables and functions */
 scalar_t__ BPF_BUFMODE_ZBUF ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  ZBUF_FLAG_ASSIGNED ; 

void
bpf_zerocopy_buf_reclaimed(struct bpf_d *d)
{
	struct zbuf *zb;

	KASSERT(d->bd_bufmode == BPF_BUFMODE_ZBUF,
	    ("bpf_zerocopy_reclaim_buf: not in zbuf mode"));

	KASSERT(d->bd_fbuf != NULL,
	    ("bpf_zerocopy_buf_reclaimed: NULL free buf"));
	zb = (struct zbuf *)d->bd_fbuf;
	zb->zb_flags &= ~ZBUF_FLAG_ASSIGNED;
}
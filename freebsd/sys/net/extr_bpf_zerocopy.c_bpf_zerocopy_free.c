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
struct zbuf {int dummy; } ;
struct bpf_d {scalar_t__ bd_bufmode; scalar_t__ bd_fbuf; scalar_t__ bd_hbuf; scalar_t__ bd_sbuf; } ;

/* Variables and functions */
 scalar_t__ BPF_BUFMODE_ZBUF ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  zbuf_free (struct zbuf*) ; 

void
bpf_zerocopy_free(struct bpf_d *d)
{
	struct zbuf *zb;

	KASSERT(d->bd_bufmode == BPF_BUFMODE_ZBUF,
	    ("bpf_zerocopy_free: not in zbuf mode"));

	zb = (struct zbuf *)d->bd_sbuf;
	if (zb != NULL)
		zbuf_free(zb);
	zb = (struct zbuf *)d->bd_hbuf;
	if (zb != NULL)
		zbuf_free(zb);
	zb = (struct zbuf *)d->bd_fbuf;
	if (zb != NULL)
		zbuf_free(zb);
}
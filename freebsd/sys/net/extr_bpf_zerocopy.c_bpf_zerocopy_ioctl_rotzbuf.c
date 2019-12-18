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
struct zbuf {scalar_t__ zb_uaddr; } ;
struct thread {int dummy; } ;
struct bpf_zbuf {int /*<<< orphan*/  bz_buflen; void* bz_bufa; } ;
struct bpf_d {scalar_t__ bd_slen; int /*<<< orphan*/  bd_hlen; int /*<<< orphan*/ * bd_hbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPFD_LOCK (struct bpf_d*) ; 
 int /*<<< orphan*/  BPFD_UNLOCK (struct bpf_d*) ; 
 int /*<<< orphan*/  ROTATE_BUFFERS (struct bpf_d*) ; 
 int /*<<< orphan*/  bzero (struct bpf_zbuf*,int) ; 

int
bpf_zerocopy_ioctl_rotzbuf(struct thread *td, struct bpf_d *d,
    struct bpf_zbuf *bz)
{
	struct zbuf *bzh;

	bzero(bz, sizeof(*bz));
	BPFD_LOCK(d);
	if (d->bd_hbuf == NULL && d->bd_slen != 0) {
		ROTATE_BUFFERS(d);
		bzh = (struct zbuf *)d->bd_hbuf;
		bz->bz_bufa = (void *)bzh->zb_uaddr;
		bz->bz_buflen = d->bd_hlen;
	}
	BPFD_UNLOCK(d);
	return (0);
}
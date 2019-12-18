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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct zbuf {int zb_flags; int zb_numpages; int /*<<< orphan*/ * zb_pages; } ;
struct bpf_zbuf_header {int dummy; } ;
struct bpf_d {scalar_t__ bd_bufmode; } ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 scalar_t__ BPF_BUFMODE_ZBUF ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PAGE_SIZE ; 
 int ZBUF_FLAG_ASSIGNED ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int min (int,int) ; 
 scalar_t__ sf_buf_kva (int /*<<< orphan*/ ) ; 

void
bpf_zerocopy_append_bytes(struct bpf_d *d, caddr_t buf, u_int offset,
    void *src, u_int len)
{
	u_int count, page, poffset;
	u_char *src_bytes;
	struct zbuf *zb;

	KASSERT(d->bd_bufmode == BPF_BUFMODE_ZBUF,
	    ("bpf_zerocopy_append_bytes: not in zbuf mode"));
	KASSERT(buf != NULL, ("bpf_zerocopy_append_bytes: NULL buf"));

	src_bytes = (u_char *)src;
	zb = (struct zbuf *)buf;

	KASSERT((zb->zb_flags & ZBUF_FLAG_ASSIGNED) == 0,
	    ("bpf_zerocopy_append_bytes: ZBUF_FLAG_ASSIGNED"));

	/*
	 * Scatter-gather copy to user pages mapped into kernel address space
	 * using sf_bufs: copy up to a page at a time.
	 */
	offset += sizeof(struct bpf_zbuf_header);
	page = offset / PAGE_SIZE;
	poffset = offset % PAGE_SIZE;
	while (len > 0) {
		KASSERT(page < zb->zb_numpages, ("bpf_zerocopy_append_bytes:"
		   " page overflow (%d p %d np)\n", page, zb->zb_numpages));

		count = min(len, PAGE_SIZE - poffset);
		bcopy(src_bytes, ((u_char *)sf_buf_kva(zb->zb_pages[page])) +
		    poffset, count);
		poffset += count;
		if (poffset == PAGE_SIZE) {
			poffset = 0;
			page++;
		}
		KASSERT(poffset < PAGE_SIZE,
		    ("bpf_zerocopy_append_bytes: page offset overflow (%d)",
		    poffset));
		len -= count;
		src_bytes += count;
	}
}
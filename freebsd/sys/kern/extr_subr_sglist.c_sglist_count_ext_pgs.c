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
typedef  scalar_t__ vm_paddr_t ;
struct mbuf_ext_pgs {size_t hdr_len; int first_pg_off; int npgs; scalar_t__* pa; size_t trail_len; int /*<<< orphan*/ * trail; int /*<<< orphan*/ * hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 size_t MIN (size_t,size_t) ; 
 int mbuf_ext_pg_len (struct mbuf_ext_pgs*,int,int) ; 
 scalar_t__ sglist_count (int /*<<< orphan*/ *,size_t) ; 

int
sglist_count_ext_pgs(struct mbuf_ext_pgs *ext_pgs, size_t off, size_t len)
{
	vm_paddr_t nextaddr, paddr;
	size_t seglen, segoff;
	int i, nsegs, pglen, pgoff;

	if (len == 0)
		return (0);

	nsegs = 0;
	if (ext_pgs->hdr_len != 0) {
		if (off >= ext_pgs->hdr_len) {
			off -= ext_pgs->hdr_len;
		} else {
			seglen = ext_pgs->hdr_len - off;
			segoff = off;
			seglen = MIN(seglen, len);
			off = 0;
			len -= seglen;
			nsegs += sglist_count(&ext_pgs->hdr[segoff], seglen);
		}
	}
	nextaddr = 0;
	pgoff = ext_pgs->first_pg_off;
	for (i = 0; i < ext_pgs->npgs && len > 0; i++) {
		pglen = mbuf_ext_pg_len(ext_pgs, i, pgoff);
		if (off >= pglen) {
			off -= pglen;
			pgoff = 0;
			continue;
		}
		seglen = pglen - off;
		segoff = pgoff + off;
		off = 0;
		seglen = MIN(seglen, len);
		len -= seglen;
		paddr = ext_pgs->pa[i] + segoff;
		if (paddr != nextaddr)
			nsegs++;
		nextaddr = paddr + seglen;
		pgoff = 0;
	};
	if (len != 0) {
		seglen = MIN(len, ext_pgs->trail_len - off);
		len -= seglen;
		nsegs += sglist_count(&ext_pgs->trail[off], seglen);
	}
	KASSERT(len == 0, ("len != 0"));
	return (nsegs);
}
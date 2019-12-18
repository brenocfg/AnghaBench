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
struct sglist {int dummy; } ;
struct mbuf_ext_pgs {size_t hdr_len; int first_pg_off; int npgs; size_t trail_len; int /*<<< orphan*/ * trail; scalar_t__* pa; int /*<<< orphan*/ * hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 size_t MIN (size_t,size_t) ; 
 int mbuf_ext_pg_len (struct mbuf_ext_pgs*,int,int) ; 
 int sglist_append (struct sglist*,int /*<<< orphan*/ *,size_t) ; 
 int sglist_append_phys (struct sglist*,scalar_t__,size_t) ; 

int
sglist_append_ext_pgs(struct sglist *sg, struct mbuf_ext_pgs *ext_pgs,
    size_t off, size_t len)
{
	size_t seglen, segoff;
	vm_paddr_t paddr;
	int error, i, pglen, pgoff;

	error = 0;
	if (ext_pgs->hdr_len != 0) {
		if (off >= ext_pgs->hdr_len) {
			off -= ext_pgs->hdr_len;
		} else {
			seglen = ext_pgs->hdr_len - off;
			segoff = off;
			seglen = MIN(seglen, len);
			off = 0;
			len -= seglen;
			error = sglist_append(sg,
			    &ext_pgs->hdr[segoff], seglen);
		}
	}
	pgoff = ext_pgs->first_pg_off;
	for (i = 0; i < ext_pgs->npgs && error == 0 && len > 0; i++) {
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
		error = sglist_append_phys(sg, paddr, seglen);
		pgoff = 0;
	};
	if (error == 0 && len > 0) {
		seglen = MIN(len, ext_pgs->trail_len - off);
		len -= seglen;
		error = sglist_append(sg,
		    &ext_pgs->trail[off], seglen);
	}
	if (error == 0)
		KASSERT(len == 0, ("len != 0"));
	return (error);
}
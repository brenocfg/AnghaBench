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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  void* vm_paddr_t ;
struct sgsave {int dummy; } ;
struct sglist_seg {size_t ss_len; void* ss_paddr; } ;
struct sglist {scalar_t__ sg_maxseg; int sg_nseg; struct sglist_seg* sg_segs; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  SGLIST_RESTORE (struct sglist*,struct sgsave) ; 
 int /*<<< orphan*/  SGLIST_SAVE (struct sglist*,struct sgsave) ; 
 void* VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 int _sglist_append_range (struct sglist*,struct sglist_seg**,void*,size_t) ; 
 size_t min (scalar_t__,size_t) ; 

int
sglist_append_vmpages(struct sglist *sg, vm_page_t *m, size_t pgoff,
    size_t len)
{
	struct sgsave save;
	struct sglist_seg *ss;
	vm_paddr_t paddr;
	size_t seglen;
	int error, i;

	if (sg->sg_maxseg == 0)
		return (EINVAL);
	if (len == 0)
		return (0);

	SGLIST_SAVE(sg, save);
	i = 0;
	if (sg->sg_nseg == 0) {
		seglen = min(PAGE_SIZE - pgoff, len);
		sg->sg_segs[0].ss_paddr = VM_PAGE_TO_PHYS(m[0]) + pgoff;
		sg->sg_segs[0].ss_len = seglen;
		sg->sg_nseg = 1;
		pgoff = 0;
		len -= seglen;
		i++;
	}
	ss = &sg->sg_segs[sg->sg_nseg - 1];
	for (; len > 0; i++, len -= seglen) {
		seglen = min(PAGE_SIZE - pgoff, len);
		paddr = VM_PAGE_TO_PHYS(m[i]) + pgoff;
		error = _sglist_append_range(sg, &ss, paddr, seglen);
		if (error) {
			SGLIST_RESTORE(sg, save);
			return (error);
		}
		pgoff = 0;
	}
	return (0);
}
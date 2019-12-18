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
struct sgsave {int dummy; } ;
struct sglist_seg {size_t ss_len; scalar_t__ ss_paddr; } ;
struct sglist {scalar_t__ sg_maxseg; int sg_nseg; struct sglist_seg* sg_segs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SGLIST_RESTORE (struct sglist*,struct sgsave) ; 
 int /*<<< orphan*/  SGLIST_SAVE (struct sglist*,struct sgsave) ; 
 int _sglist_append_range (struct sglist*,struct sglist_seg**,scalar_t__,size_t) ; 

int
sglist_append_sglist(struct sglist *sg, struct sglist *source, size_t offset,
    size_t length)
{
	struct sgsave save;
	struct sglist_seg *ss;
	size_t seglen;
	int error, i;

	if (sg->sg_maxseg == 0 || length == 0)
		return (EINVAL);
	SGLIST_SAVE(sg, save);
	error = EINVAL;
	ss = &sg->sg_segs[sg->sg_nseg - 1];
	for (i = 0; i < source->sg_nseg; i++) {
		if (offset >= source->sg_segs[i].ss_len) {
			offset -= source->sg_segs[i].ss_len;
			continue;
		}
		seglen = source->sg_segs[i].ss_len - offset;
		if (seglen > length)
			seglen = length;
		error = _sglist_append_range(sg, &ss,
		    source->sg_segs[i].ss_paddr + offset, seglen);
		if (error)
			break;
		offset = 0;
		length -= seglen;
		if (length == 0)
			break;
	}
	if (length != 0)
		error = EINVAL;
	if (error)
		SGLIST_RESTORE(sg, save);
	return (error);
}
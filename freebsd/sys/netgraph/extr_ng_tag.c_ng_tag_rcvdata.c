#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {int len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct m_tag {int dummy; } ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/ * hook_p ;
typedef  TYPE_3__* hinfo_p ;
struct TYPE_5__ {int recvOctets; int recvMatchOctets; int xmitOctets; int /*<<< orphan*/  xmitFrames; int /*<<< orphan*/  recvMatchFrames; int /*<<< orphan*/  recvFrames; } ;
struct TYPE_6__ {scalar_t__ in_tag_cookie; scalar_t__ in_tag_id; scalar_t__ in_tag_len; scalar_t__ out_tag_cookie; scalar_t__ out_tag_id; scalar_t__ out_tag_len; int /*<<< orphan*/  out_tag_data; TYPE_2__ stats; int /*<<< orphan*/ * hi_nonmatch; int /*<<< orphan*/ * hi_match; scalar_t__ strip; int /*<<< orphan*/  in_tag_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 struct mbuf* NGI_M (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FWD_ITEM_HOOK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* NG_HOOK_PRIVATE (int /*<<< orphan*/ *) ; 
 struct m_tag* m_tag_alloc (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_tag_delete (struct mbuf*,struct m_tag*) ; 
 struct m_tag* m_tag_locate (struct mbuf*,scalar_t__,scalar_t__,struct m_tag*) ; 
 int /*<<< orphan*/  m_tag_prepend (struct mbuf*,struct m_tag*) ; 
 scalar_t__ memcmp (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
ng_tag_rcvdata(hook_p hook, item_p item)
{
	struct mbuf *m;
	struct m_tag *tag = NULL;
	const hinfo_p hip = NG_HOOK_PRIVATE(hook);
	uint16_t type, tag_len;
	uint32_t cookie;
	hinfo_p dhip;
	hook_p dest;
	int totlen;
	int found = 0, error = 0;

	m = NGI_M(item);	/* 'item' still owns it.. we are peeking */
	totlen = m->m_pkthdr.len;

#ifdef NG_TAG_DEBUG
	hip->stats.recvFrames++;
	hip->stats.recvOctets += totlen;
#endif

	/* Looking up incoming tag. */
	cookie = hip->in_tag_cookie;
	type = hip->in_tag_id;
	tag_len = hip->in_tag_len;

	/*
	 * We treat case of all zeroes specially (that is, cookie and
	 * type are equal to zero), as we assume that such tag
	 * can never occur in the wild.  So we don't waste time trying
	 * to find such tag (for example, these are zeroes after hook
	 * creation in default structures).
	 */
	if ((cookie != 0) || (type != 0)) {
		tag = m_tag_locate(m, cookie, type, NULL);
		while (tag != NULL) {
			if (memcmp((void *)(tag + 1),
			    hip->in_tag_data, tag_len) == 0) {
				found = 1;
				break;
			}
			tag = m_tag_locate(m, cookie, type, tag);
		}
	}
	
	/* See if we got a match and find destination hook. */
	if (found) {
#ifdef NG_TAG_DEBUG
		hip->stats.recvMatchFrames++;
		hip->stats.recvMatchOctets += totlen;
#endif
		if (hip->strip)
			m_tag_delete(m, tag);
		dest = hip->hi_match;
	} else
		dest = hip->hi_nonmatch;
	if (dest == NULL) {
		NG_FREE_ITEM(item);
		return (0);
	}

	/* Deliver frame out destination hook. */
	dhip = NG_HOOK_PRIVATE(dest);

#ifdef NG_TAG_DEBUG
	dhip->stats.xmitOctets += totlen;
	dhip->stats.xmitFrames++;
#endif
	
	cookie = dhip->out_tag_cookie;
	type = dhip->out_tag_id;
	tag_len = dhip->out_tag_len;
	
	if ((cookie != 0) || (type != 0)) {
		tag = m_tag_alloc(cookie, type, tag_len, M_NOWAIT);
		/* XXX may be free the mbuf if tag allocation failed? */
		if (tag != NULL) {
			if (tag_len != 0) {
				/* copy tag data to its place */
				memcpy((void *)(tag + 1),
				    dhip->out_tag_data, tag_len);
			}
			m_tag_prepend(m, tag);
		}
	}
	
	NG_FWD_ITEM_HOOK(error, item, dest);
	return (error);
}
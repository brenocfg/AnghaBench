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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct val_anchors {int dummy; } ;
struct trust_anchor {int /*<<< orphan*/  lock; scalar_t__ numDNSKEY; scalar_t__ numDS; } ;

/* Variables and functions */
 struct trust_anchor* anchor_find (struct val_anchors*,int /*<<< orphan*/ *,int,size_t,scalar_t__) ; 
 size_t anchor_list_keytags (struct trust_anchor*,scalar_t__*,scalar_t__) ; 
 scalar_t__* calloc (scalar_t__,int) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 

int
anchor_has_keytag(struct val_anchors* anchors, uint8_t* name, int namelabs,
	size_t namelen, uint16_t dclass, uint16_t keytag)
{
	uint16_t* taglist;
	uint16_t* tl;
	size_t numtag, i;
	struct trust_anchor* anchor = anchor_find(anchors,
		name, namelabs, namelen, dclass);
	if(!anchor)
		return 0;
	if(!anchor->numDS && !anchor->numDNSKEY) {
		lock_basic_unlock(&anchor->lock);
		return 0;
	}

	taglist = calloc(anchor->numDS + anchor->numDNSKEY, sizeof(*taglist));
	if(!taglist) {
		lock_basic_unlock(&anchor->lock);
		return 0;
	}

	numtag = anchor_list_keytags(anchor, taglist,
		anchor->numDS+anchor->numDNSKEY);
	lock_basic_unlock(&anchor->lock);
	if(!numtag) {
		free(taglist);
		return 0;
	}
	tl = taglist;
	for(i=0; i<numtag; i++) {
		if(*tl == keytag) {
			free(taglist);
			return 1;
		}
		tl++;
	}
	free(taglist);
	return 0;
}
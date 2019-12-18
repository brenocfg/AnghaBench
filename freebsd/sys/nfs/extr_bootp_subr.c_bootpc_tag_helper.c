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
struct bootpc_tagcontext {int badtag; int badopt; scalar_t__ taglen; int foundopt; scalar_t__ buf; unsigned char overload; } ;

/* Variables and functions */
 unsigned char TAG_END ; 
 scalar_t__ TAG_MAXLEN ; 
 unsigned char TAG_OVERLOAD ; 
 unsigned char TAG_PAD ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char*,int) ; 

__attribute__((used)) static void
bootpc_tag_helper(struct bootpc_tagcontext *tctx,
    unsigned char *start, int len, int tag)
{
	unsigned char *j;
	unsigned char *ej;
	unsigned char code;

	if (tctx->badtag != 0 || tctx->badopt != 0)
		return;

	j = start;
	ej = j + len;

	while (j < ej) {
		code = *j++;
		if (code == TAG_PAD)
			continue;
		if (code == TAG_END)
			return;
		if (j >= ej || j + *j + 1 > ej) {
			tctx->badopt = 1;
			return;
		}
		len = *j++;
		if (code == tag) {
			if (tctx->taglen + len > TAG_MAXLEN) {
				tctx->badtag = 1;
				return;
			}
			tctx->foundopt = 1;
			if (len > 0)
				memcpy(tctx->buf + tctx->taglen,
				       j, len);
			tctx->taglen += len;
		}
		if (code == TAG_OVERLOAD)
			tctx->overload = *j;

		j += len;
	}
}
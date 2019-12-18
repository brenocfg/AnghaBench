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
struct bootpc_tagcontext {int overload; scalar_t__ badopt; scalar_t__ badtag; scalar_t__ foundopt; size_t taglen; char* buf; } ;
struct bootp_packet {unsigned char* vend; scalar_t__ sname; scalar_t__ file; } ;

/* Variables and functions */
 int OVERLOAD_FILE ; 
 int OVERLOAD_SNAME ; 
 scalar_t__ bootpc_hascookie (struct bootp_packet*) ; 
 int /*<<< orphan*/  bootpc_tag_helper (struct bootpc_tagcontext*,unsigned char*,int,int) ; 

__attribute__((used)) static unsigned char *
bootpc_tag(struct bootpc_tagcontext *tctx,
    struct bootp_packet *bp, int len, int tag)
{
	tctx->overload = 0;
	tctx->badopt = 0;
	tctx->badtag = 0;
	tctx->foundopt = 0;
	tctx->taglen = 0;

	if (bootpc_hascookie(bp) == 0)
		return NULL;

	bootpc_tag_helper(tctx, &bp->vend[4],
			  (unsigned char *) bp + len - &bp->vend[4], tag);

	if ((tctx->overload & OVERLOAD_FILE) != 0)
		bootpc_tag_helper(tctx,
				  (unsigned char *) bp->file,
				  sizeof(bp->file),
				  tag);
	if ((tctx->overload & OVERLOAD_SNAME) != 0)
		bootpc_tag_helper(tctx,
				  (unsigned char *) bp->sname,
				  sizeof(bp->sname),
				  tag);

	if (tctx->badopt != 0 || tctx->badtag != 0 || tctx->foundopt == 0)
		return NULL;
	tctx->buf[tctx->taglen] = '\0';
	return tctx->buf;
}
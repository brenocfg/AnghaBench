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
typedef  int u_int32_t ;
struct csa_info {int /*<<< orphan*/  res; } ;
struct csa_chinfo {scalar_t__ dir; int fmt; int /*<<< orphan*/  buffer; struct csa_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;
typedef  int /*<<< orphan*/  csa_res ;

/* Variables and functions */
 int AFMT_S8 ; 
 int AFMT_U8 ; 
 int /*<<< orphan*/  BA1_CBA ; 
 int /*<<< orphan*/  BA1_PBA ; 
 scalar_t__ PCMDIR_PLAY ; 
 int csa_readmem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sndbuf_getbufaddr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
csachan_getptr(kobj_t obj, void *data)
{
	struct csa_chinfo *ch = data;
	struct csa_info *csa = ch->parent;
	csa_res *resp;
	u_int32_t ptr;

	resp = &csa->res;

	if (ch->dir == PCMDIR_PLAY) {
		ptr = csa_readmem(resp, BA1_PBA) - sndbuf_getbufaddr(ch->buffer);
		if ((ch->fmt & AFMT_U8) != 0 || (ch->fmt & AFMT_S8) != 0)
			ptr >>= 1;
	} else {
		ptr = csa_readmem(resp, BA1_CBA) - sndbuf_getbufaddr(ch->buffer);
		if ((ch->fmt & AFMT_U8) != 0 || (ch->fmt & AFMT_S8) != 0)
			ptr >>= 1;
	}

	return (ptr);
}
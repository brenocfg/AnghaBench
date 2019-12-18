#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nl_msg {size_t nm_size; TYPE_1__* nm_nlh; } ;
struct TYPE_2__ {size_t nlmsg_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL_DBG (int,char*,struct nl_msg*,size_t,int,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

void *nlmsg_reserve(struct nl_msg *n, size_t len, int pad)
{
	void *buf = n->nm_nlh;
	size_t nlmsg_len = n->nm_nlh->nlmsg_len;
	size_t tlen;

	tlen = pad ? ((len + (pad - 1)) & ~(pad - 1)) : len;

	if ((tlen + nlmsg_len) > n->nm_size)
		return NULL;

	buf += nlmsg_len;
	n->nm_nlh->nlmsg_len += tlen;

	if (tlen > len)
		memset(buf + len, 0, tlen - len);

	NL_DBG(2, "msg %p: Reserved %zu bytes, pad=%d, nlmsg_len=%d\n",
		  n, len, pad, n->nm_nlh->nlmsg_len);

	return buf;
}
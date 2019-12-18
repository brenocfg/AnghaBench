#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nlmsghdr {int dummy; } ;
struct nl_msg {int nm_refcnt; int nm_protocol; size_t nm_size; TYPE_1__* nm_nlh; } ;
struct TYPE_3__ {int /*<<< orphan*/  nlmsg_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL_DBG (int,char*,struct nl_msg*,size_t) ; 
 struct nl_msg* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct nl_msg*) ; 
 TYPE_1__* malloc (size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlmsg_total_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nl_msg *__nlmsg_alloc(size_t len)
{
	struct nl_msg *nm;

	nm = calloc(1, sizeof(*nm));
	if (!nm)
		goto errout;

	nm->nm_refcnt = 1;

	nm->nm_nlh = malloc(len);
	if (!nm->nm_nlh)
		goto errout;

	memset(nm->nm_nlh, 0, sizeof(struct nlmsghdr));

	nm->nm_protocol = -1;
	nm->nm_size = len;
	nm->nm_nlh->nlmsg_len = nlmsg_total_size(0);

	NL_DBG(2, "msg %p: Allocated new message, maxlen=%zu\n", nm, len);

	return nm;
errout:
	free(nm);
	return NULL;
}
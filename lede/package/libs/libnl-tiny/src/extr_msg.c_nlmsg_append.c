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
struct nl_msg {int dummy; } ;

/* Variables and functions */
 int NLE_NOMEM ; 
 int /*<<< orphan*/  NL_DBG (int,char*,struct nl_msg*,size_t,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 void* nlmsg_reserve (struct nl_msg*,size_t,int) ; 

int nlmsg_append(struct nl_msg *n, void *data, size_t len, int pad)
{
	void *tmp;

	tmp = nlmsg_reserve(n, len, pad);
	if (tmp == NULL)
		return -NLE_NOMEM;

	memcpy(tmp, data, len);
	NL_DBG(2, "msg %p: Appended %zu bytes with padding %d\n", n, len, pad);

	return 0;
}
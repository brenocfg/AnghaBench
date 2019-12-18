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
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct nbd_device {int /*<<< orphan*/  index; int /*<<< orphan*/  config_refs; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  NBD_DEVICE_CONNECTED ; 
 int /*<<< orphan*/  NBD_DEVICE_INDEX ; 
 int /*<<< orphan*/  NBD_DEVICE_ITEM ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ refcount_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int populate_nbd_status(struct nbd_device *nbd, struct sk_buff *reply)
{
	struct nlattr *dev_opt;
	u8 connected = 0;
	int ret;

	/* This is a little racey, but for status it's ok.  The
	 * reason we don't take a ref here is because we can't
	 * take a ref in the index == -1 case as we would need
	 * to put under the nbd_index_mutex, which could
	 * deadlock if we are configured to remove ourselves
	 * once we're disconnected.
	 */
	if (refcount_read(&nbd->config_refs))
		connected = 1;
	dev_opt = nla_nest_start_noflag(reply, NBD_DEVICE_ITEM);
	if (!dev_opt)
		return -EMSGSIZE;
	ret = nla_put_u32(reply, NBD_DEVICE_INDEX, nbd->index);
	if (ret)
		return -EMSGSIZE;
	ret = nla_put_u8(reply, NBD_DEVICE_CONNECTED,
			 connected);
	if (ret)
		return -EMSGSIZE;
	nla_nest_end(reply, dev_opt);
	return 0;
}
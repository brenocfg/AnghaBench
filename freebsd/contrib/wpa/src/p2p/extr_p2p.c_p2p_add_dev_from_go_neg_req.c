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
typedef  int /*<<< orphan*/  u8 ;
struct p2p_message {int dummy; } ;
struct p2p_device {int /*<<< orphan*/  last_seen; } ;
struct p2p_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_get_reltime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_add_dev_info (struct p2p_data*,int /*<<< orphan*/  const*,struct p2p_device*,struct p2p_message*) ; 
 struct p2p_device* p2p_create_device (struct p2p_data*,int /*<<< orphan*/  const*) ; 
 struct p2p_device* p2p_get_device (struct p2p_data*,int /*<<< orphan*/  const*) ; 

struct p2p_device * p2p_add_dev_from_go_neg_req(struct p2p_data *p2p,
						const u8 *addr,
						struct p2p_message *msg)
{
	struct p2p_device *dev;

	dev = p2p_get_device(p2p, addr);
	if (dev) {
		os_get_reltime(&dev->last_seen);
		return dev; /* already known */
	}

	dev = p2p_create_device(p2p, addr);
	if (dev == NULL)
		return NULL;

	p2p_add_dev_info(p2p, addr, dev, msg);

	return dev;
}
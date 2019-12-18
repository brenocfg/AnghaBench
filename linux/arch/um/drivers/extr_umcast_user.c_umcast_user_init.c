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
struct umcast_data {void* dev; void* remote_addr; void* listen_addr; int /*<<< orphan*/  lport; scalar_t__ unicast; int /*<<< orphan*/  rport; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 void* new_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int umcast_user_init(void *data, void *dev)
{
	struct umcast_data *pri = data;

	pri->remote_addr = new_addr(pri->addr, pri->rport);
	if (pri->unicast)
		pri->listen_addr = new_addr(NULL, pri->lport);
	else
		pri->listen_addr = pri->remote_addr;
	pri->dev = dev;
	return 0;
}
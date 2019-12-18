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
typedef  void* u8 ;
struct p2p_data {void* client_timeout; void* go_timeout; } ;

/* Variables and functions */

void p2p_set_config_timeout(struct p2p_data *p2p, u8 go_timeout,
			    u8 client_timeout)
{
	if (p2p) {
		p2p->go_timeout = go_timeout;
		p2p->client_timeout = client_timeout;
	}
}
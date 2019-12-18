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
struct p2p_data {TYPE_1__* cfg; } ;
struct TYPE_2__ {unsigned int passphrase_len; } ;

/* Variables and functions */

int p2p_set_passphrase_len(struct p2p_data *p2p, unsigned int len)
{
	if (len < 8 || len > 63)
		return -1;
	p2p->cfg->passphrase_len = len;
	return 0;
}
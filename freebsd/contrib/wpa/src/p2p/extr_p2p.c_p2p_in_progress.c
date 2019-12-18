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
struct p2p_data {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ P2P_IDLE ; 
 scalar_t__ P2P_PROVISIONING ; 
 scalar_t__ P2P_SEARCH ; 

int p2p_in_progress(struct p2p_data *p2p)
{
	if (p2p == NULL)
		return 0;
	if (p2p->state == P2P_SEARCH)
		return 2;
	return p2p->state != P2P_IDLE && p2p->state != P2P_PROVISIONING;
}
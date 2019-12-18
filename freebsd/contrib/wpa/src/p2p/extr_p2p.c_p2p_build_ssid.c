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
typedef  int /*<<< orphan*/  u8 ;
struct p2p_data {TYPE_1__* cfg; } ;
struct TYPE_2__ {size_t ssid_postfix_len; int /*<<< orphan*/  ssid_postfix; } ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_WILDCARD_SSID ; 
 size_t P2P_WILDCARD_SSID_LEN ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  p2p_random (char*,int) ; 

void p2p_build_ssid(struct p2p_data *p2p, u8 *ssid, size_t *ssid_len)
{
	os_memcpy(ssid, P2P_WILDCARD_SSID, P2P_WILDCARD_SSID_LEN);
	p2p_random((char *) &ssid[P2P_WILDCARD_SSID_LEN], 2);
	os_memcpy(&ssid[P2P_WILDCARD_SSID_LEN + 2],
		  p2p->cfg->ssid_postfix, p2p->cfg->ssid_postfix_len);
	*ssid_len = P2P_WILDCARD_SSID_LEN + 2 + p2p->cfg->ssid_postfix_len;
}
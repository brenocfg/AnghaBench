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
struct p2p_go_neg_results {int /*<<< orphan*/  passphrase; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;
struct p2p_data {TYPE_1__* cfg; scalar_t__ ssid_set; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;
struct TYPE_2__ {int /*<<< orphan*/  passphrase_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_build_ssid (struct p2p_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_random (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int p2p_go_params(struct p2p_data *p2p, struct p2p_go_neg_results *params)
{
	if (p2p->ssid_set) {
		os_memcpy(params->ssid, p2p->ssid, p2p->ssid_len);
		params->ssid_len = p2p->ssid_len;
	} else {
		p2p_build_ssid(p2p, params->ssid, &params->ssid_len);
	}
	p2p->ssid_set = 0;

	p2p_random(params->passphrase, p2p->cfg->passphrase_len);
	return 0;
}
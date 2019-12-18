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
struct dpp_configuration {scalar_t__ ssid_len; int /*<<< orphan*/  passphrase; int /*<<< orphan*/  akm; int /*<<< orphan*/  psk_set; } ;

/* Variables and functions */
 scalar_t__ dpp_akm_psk (int /*<<< orphan*/ ) ; 
 scalar_t__ dpp_akm_sae (int /*<<< orphan*/ ) ; 

int dpp_configuration_valid(const struct dpp_configuration *conf)
{
	if (conf->ssid_len == 0)
		return 0;
	if (dpp_akm_psk(conf->akm) && !conf->passphrase && !conf->psk_set)
		return 0;
	if (dpp_akm_sae(conf->akm) && !conf->passphrase)
		return 0;
	return 1;
}
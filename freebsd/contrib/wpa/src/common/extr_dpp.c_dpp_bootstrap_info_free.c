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
struct dpp_bootstrap_info {int /*<<< orphan*/  pubkey; struct dpp_bootstrap_info* info; struct dpp_bootstrap_info* uri; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct dpp_bootstrap_info*) ; 

void dpp_bootstrap_info_free(struct dpp_bootstrap_info *info)
{
	if (!info)
		return;
	os_free(info->uri);
	os_free(info->info);
	EVP_PKEY_free(info->pubkey);
	os_free(info);
}
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
struct dpp_configurator {struct dpp_configurator* kid; int /*<<< orphan*/  csign; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct dpp_configurator*) ; 

void dpp_configurator_free(struct dpp_configurator *conf)
{
	if (!conf)
		return;
	EVP_PKEY_free(conf->csign);
	os_free(conf->kid);
	os_free(conf);
}
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
struct dpp_configuration {int /*<<< orphan*/  group_id; int /*<<< orphan*/  passphrase; } ;

/* Variables and functions */
 int /*<<< orphan*/  bin_clear_free (struct dpp_configuration*,int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_clear_free (int /*<<< orphan*/ ) ; 

void dpp_configuration_free(struct dpp_configuration *conf)
{
	if (!conf)
		return;
	str_clear_free(conf->passphrase);
	os_free(conf->group_id);
	bin_clear_free(conf, sizeof(*conf));
}
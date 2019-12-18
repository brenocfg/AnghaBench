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
struct table_info {int dummy; } ;
struct chash_cfg {int mask4; int mask6; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,...) ; 

__attribute__((used)) static void
ta_print_chash_config(void *ta_state, struct table_info *ti, char *buf,
    size_t bufsize)
{
	struct chash_cfg *cfg;

	cfg = (struct chash_cfg *)ta_state;

	if (cfg->mask4 != 32 || cfg->mask6 != 128)
		snprintf(buf, bufsize, "%s masks=/%d,/%d", "addr:hash",
		    cfg->mask4, cfg->mask6);
	else
		snprintf(buf, bufsize, "%s", "addr:hash");
}
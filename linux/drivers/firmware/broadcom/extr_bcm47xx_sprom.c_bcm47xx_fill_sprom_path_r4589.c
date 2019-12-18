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
struct ssb_sprom_core_pwr_info {int /*<<< orphan*/ * pa_5gh; int /*<<< orphan*/ * pa_5gl; int /*<<< orphan*/ * pa_5g; int /*<<< orphan*/  maxpwr_5gl; int /*<<< orphan*/  maxpwr_5gh; int /*<<< orphan*/  maxpwr_5g; int /*<<< orphan*/ * pa_2g; int /*<<< orphan*/  itssi_5g; int /*<<< orphan*/  itssi_2g; int /*<<< orphan*/  maxpwr_2g; } ;
struct ssb_sprom {struct ssb_sprom_core_pwr_info* core_pwr_info; } ;
typedef  int /*<<< orphan*/  postfix ;

/* Variables and functions */
 int ARRAY_SIZE (struct ssb_sprom_core_pwr_info*) ; 
 int /*<<< orphan*/  nvram_read_u16 (char const*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvram_read_u8 (char const*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void bcm47xx_fill_sprom_path_r4589(struct ssb_sprom *sprom,
					  const char *prefix, bool fallback)
{
	char postfix[2];
	int i;

	for (i = 0; i < ARRAY_SIZE(sprom->core_pwr_info); i++) {
		struct ssb_sprom_core_pwr_info *pwr_info;

		pwr_info = &sprom->core_pwr_info[i];

		snprintf(postfix, sizeof(postfix), "%i", i);
		nvram_read_u8(prefix, postfix, "maxp2ga",
			      &pwr_info->maxpwr_2g, 0, fallback);
		nvram_read_u8(prefix, postfix, "itt2ga",
			      &pwr_info->itssi_2g, 0, fallback);
		nvram_read_u8(prefix, postfix, "itt5ga",
			      &pwr_info->itssi_5g, 0, fallback);
		nvram_read_u16(prefix, postfix, "pa2gw0a",
			       &pwr_info->pa_2g[0], 0, fallback);
		nvram_read_u16(prefix, postfix, "pa2gw1a",
			       &pwr_info->pa_2g[1], 0, fallback);
		nvram_read_u16(prefix, postfix, "pa2gw2a",
			       &pwr_info->pa_2g[2], 0, fallback);
		nvram_read_u8(prefix, postfix, "maxp5ga",
			      &pwr_info->maxpwr_5g, 0, fallback);
		nvram_read_u8(prefix, postfix, "maxp5gha",
			      &pwr_info->maxpwr_5gh, 0, fallback);
		nvram_read_u8(prefix, postfix, "maxp5gla",
			      &pwr_info->maxpwr_5gl, 0, fallback);
		nvram_read_u16(prefix, postfix, "pa5gw0a",
			       &pwr_info->pa_5g[0], 0, fallback);
		nvram_read_u16(prefix, postfix, "pa5gw1a",
			       &pwr_info->pa_5g[1], 0, fallback);
		nvram_read_u16(prefix, postfix, "pa5gw2a",
			       &pwr_info->pa_5g[2], 0, fallback);
		nvram_read_u16(prefix, postfix, "pa5glw0a",
			       &pwr_info->pa_5gl[0], 0, fallback);
		nvram_read_u16(prefix, postfix, "pa5glw1a",
			       &pwr_info->pa_5gl[1], 0, fallback);
		nvram_read_u16(prefix, postfix, "pa5glw2a",
			       &pwr_info->pa_5gl[2], 0, fallback);
		nvram_read_u16(prefix, postfix, "pa5ghw0a",
			       &pwr_info->pa_5gh[0], 0, fallback);
		nvram_read_u16(prefix, postfix, "pa5ghw1a",
			       &pwr_info->pa_5gh[1], 0, fallback);
		nvram_read_u16(prefix, postfix, "pa5ghw2a",
			       &pwr_info->pa_5gh[2], 0, fallback);
	}
}
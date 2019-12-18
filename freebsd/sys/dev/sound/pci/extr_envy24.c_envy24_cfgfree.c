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
struct cfg_info {scalar_t__ free; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_ENVY24 ; 
 int /*<<< orphan*/  free (struct cfg_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
envy24_cfgfree(struct cfg_info *cfg) {
	if (cfg == NULL)
		return;
	if (cfg->free)
		free(cfg, M_ENVY24);
	return;
}
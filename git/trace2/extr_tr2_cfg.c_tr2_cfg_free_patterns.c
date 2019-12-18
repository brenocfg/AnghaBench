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

/* Variables and functions */
 int /*<<< orphan*/  strbuf_list_free (scalar_t__) ; 
 scalar_t__ tr2_cfg_count_patterns ; 
 scalar_t__ tr2_cfg_loaded ; 
 scalar_t__ tr2_cfg_patterns ; 

void tr2_cfg_free_patterns(void)
{
	if (tr2_cfg_patterns)
		strbuf_list_free(tr2_cfg_patterns);
	tr2_cfg_count_patterns = 0;
	tr2_cfg_loaded = 0;
}
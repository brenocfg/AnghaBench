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
 int /*<<< orphan*/  debug_tab ; 
 int parse_config_table (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,char const*) ; 

int pcap_config_hook (const char *keyword, const char *value)
{
  return parse_config_table (debug_tab, NULL, keyword, value);
}
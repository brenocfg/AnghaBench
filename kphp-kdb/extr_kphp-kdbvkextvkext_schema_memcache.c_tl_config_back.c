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
 scalar_t__ CONFIG_LIST_SIZE ; 
 int /*<<< orphan*/ * config_list ; 
 size_t config_list_pos ; 
 int /*<<< orphan*/  cur_config ; 
 int /*<<< orphan*/  tl_config_delete (int /*<<< orphan*/ ) ; 

void tl_config_back (void) {
  tl_config_delete (cur_config);
  config_list_pos --;
  if (config_list_pos < 0) {
    config_list_pos += CONFIG_LIST_SIZE;
  }
  cur_config = config_list[config_list_pos];
}
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
typedef  int /*<<< orphan*/  AspellConfig ;

/* Variables and functions */
 int /*<<< orphan*/  aspell_config_error_message (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aspell_config_replace (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int vk_aspell_config_replace (AspellConfig *c, const char *key, const char *value) {
  if (!aspell_config_replace (c, key, value)) {
    vkprintf (1, "aspell_config_replace (%p, %s, %s) fail.\n", c, key, value);
    vkprintf (1, "%s\n", aspell_config_error_message (c));
    return 0;
  }
  return 1;
}
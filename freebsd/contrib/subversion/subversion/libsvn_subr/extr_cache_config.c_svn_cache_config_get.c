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
typedef  int /*<<< orphan*/  svn_cache_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  const cache_settings ; 

const svn_cache_config_t *
svn_cache_config_get(void)
{
  return &cache_settings;
}
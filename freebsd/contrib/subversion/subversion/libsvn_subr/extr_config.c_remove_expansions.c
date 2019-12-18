#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ x_values; int /*<<< orphan*/  x_pool; } ;
typedef  TYPE_1__ svn_config_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  for_each_option (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmex_callback ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
remove_expansions(svn_config_t *cfg)
{
  if (!cfg->x_values)
    return;

  for_each_option(cfg, NULL, cfg->x_pool, rmex_callback);
  svn_pool_clear(cfg->x_pool);
  cfg->x_values = FALSE;
}
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
typedef  int /*<<< orphan*/  svn_config_t ;
struct search_groups_baton {char const* key; char const* match; int /*<<< orphan*/ * pool; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  search_groups ; 
 int /*<<< orphan*/  svn_config_enumerate2 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,struct search_groups_baton*,int /*<<< orphan*/ *) ; 

const char *svn_config_find_group(svn_config_t *cfg, const char *key,
                                  const char *master_section,
                                  apr_pool_t *pool)
{
  struct search_groups_baton gb;

  gb.key = key;
  gb.match = NULL;
  gb.pool = pool;
  (void) svn_config_enumerate2(cfg, master_section, search_groups, &gb, pool);
  return gb.match;
}
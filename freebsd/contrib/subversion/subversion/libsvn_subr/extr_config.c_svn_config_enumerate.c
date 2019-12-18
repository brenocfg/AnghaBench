#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ svn_config_t ;
typedef  int /*<<< orphan*/  (* svn_config_enumerator_t ) (int /*<<< orphan*/ ,char const*,void*) ;
struct TYPE_12__ {int /*<<< orphan*/  options; } ;
typedef  TYPE_2__ cfg_section_t ;
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ cfg_option_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 TYPE_3__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_option (TYPE_1__*,char const*,int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  make_string_from_option (char const**,TYPE_1__*,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

int
svn_config_enumerate(svn_config_t *cfg, const char *section,
                     svn_config_enumerator_t callback, void *baton)
{
  cfg_section_t *sec;
  apr_hash_index_t *opt_ndx;
  int count;
  apr_pool_t *subpool;

  find_option(cfg, section, NULL, &sec);
  if (sec == NULL)
    return 0;

  subpool = svn_pool_create(cfg->pool);
  count = 0;
  for (opt_ndx = apr_hash_first(subpool, sec->options);
       opt_ndx != NULL;
       opt_ndx = apr_hash_next(opt_ndx))
    {
      cfg_option_t *opt = apr_hash_this_val(opt_ndx);
      const char *temp_value;

      ++count;
      make_string_from_option(&temp_value, cfg, sec, opt, NULL);
      if (!callback(opt->name, temp_value, baton))
        break;
    }

  svn_pool_destroy(subpool);
  return count;
}
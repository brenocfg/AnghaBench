#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_config_t ;
typedef  int /*<<< orphan*/  (* svn_config_enumerator2_t ) (int /*<<< orphan*/ ,char const*,void*,int /*<<< orphan*/ *) ;
struct TYPE_7__ {int /*<<< orphan*/  options; } ;
typedef  TYPE_1__ cfg_section_t ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ cfg_option_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 TYPE_2__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_option (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  make_string_from_option (char const**,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

int
svn_config_enumerate2(svn_config_t *cfg, const char *section,
                      svn_config_enumerator2_t callback, void *baton,
                      apr_pool_t *pool)
{
  cfg_section_t *sec;
  apr_hash_index_t *opt_ndx;
  apr_pool_t *iteration_pool;
  int count;

  find_option(cfg, section, NULL, &sec);
  if (sec == NULL)
    return 0;

  iteration_pool = svn_pool_create(pool);
  count = 0;
  for (opt_ndx = apr_hash_first(pool, sec->options);
       opt_ndx != NULL;
       opt_ndx = apr_hash_next(opt_ndx))
    {
      cfg_option_t *opt = apr_hash_this_val(opt_ndx);
      const char *temp_value;

      ++count;
      make_string_from_option(&temp_value, cfg, sec, opt, NULL);
      svn_pool_clear(iteration_pool);
      if (!callback(opt->name, temp_value, baton, iteration_pool))
        break;
    }
  svn_pool_destroy(iteration_pool);

  return count;
}
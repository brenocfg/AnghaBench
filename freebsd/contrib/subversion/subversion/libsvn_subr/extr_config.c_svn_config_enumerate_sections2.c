#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sections; } ;
typedef  TYPE_1__ svn_config_t ;
typedef  int /*<<< orphan*/  (* svn_config_section_enumerator2_t ) (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ cfg_section_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 TYPE_2__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

int
svn_config_enumerate_sections2(svn_config_t *cfg,
                               svn_config_section_enumerator2_t callback,
                               void *baton, apr_pool_t *pool)
{
  apr_hash_index_t *sec_ndx;
  apr_pool_t *iteration_pool;
  int count = 0;

  iteration_pool = svn_pool_create(pool);
  for (sec_ndx = apr_hash_first(pool, cfg->sections);
       sec_ndx != NULL;
       sec_ndx = apr_hash_next(sec_ndx))
    {
      cfg_section_t *sec = apr_hash_this_val(sec_ndx);

      ++count;
      svn_pool_clear(iteration_pool);
      if (!callback(sec->name, baton, iteration_pool))
        break;
    }
  svn_pool_destroy(iteration_pool);

  return count;
}
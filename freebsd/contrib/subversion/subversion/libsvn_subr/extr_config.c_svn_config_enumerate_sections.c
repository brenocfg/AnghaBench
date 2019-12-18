#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sections; int /*<<< orphan*/  x_pool; } ;
typedef  TYPE_1__ svn_config_t ;
typedef  int /*<<< orphan*/  (* svn_config_section_enumerator_t ) (int /*<<< orphan*/ ,void*) ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ cfg_section_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

int
svn_config_enumerate_sections(svn_config_t *cfg,
                              svn_config_section_enumerator_t callback,
                              void *baton)
{
  apr_hash_index_t *sec_ndx;
  int count = 0;
  apr_pool_t *subpool = svn_pool_create(cfg->x_pool);

  for (sec_ndx = apr_hash_first(subpool, cfg->sections);
       sec_ndx != NULL;
       sec_ndx = apr_hash_next(sec_ndx))
    {
      void *sec_ptr;
      cfg_section_t *sec;

      apr_hash_this(sec_ndx, NULL, NULL, &sec_ptr);
      sec = sec_ptr;
      ++count;
      if (!callback(sec->name, baton))
        break;
    }

  svn_pool_destroy(subpool);
  return count;
}
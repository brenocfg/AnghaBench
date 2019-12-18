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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {void* read_only; void* option_names_case_sensitive; void* section_names_case_sensitive; void* tmp_value; void* tmp_key; void* x_values; int /*<<< orphan*/  x_pool; int /*<<< orphan*/ * pool; int /*<<< orphan*/  sections; } ;
typedef  TYPE_1__ svn_config_t ;
typedef  void* svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_hash__make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ *) ; 
 void* svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_config_create2(svn_config_t **cfgp,
                   svn_boolean_t section_names_case_sensitive,
                   svn_boolean_t option_names_case_sensitive,
                   apr_pool_t *result_pool)
{
  svn_config_t *cfg = apr_palloc(result_pool, sizeof(*cfg));

  cfg->sections = svn_hash__make(result_pool);
  cfg->pool = result_pool;
  cfg->x_pool = svn_pool_create(result_pool);
  cfg->x_values = FALSE;
  cfg->tmp_key = svn_stringbuf_create_empty(result_pool);
  cfg->tmp_value = svn_stringbuf_create_empty(result_pool);
  cfg->section_names_case_sensitive = section_names_case_sensitive;
  cfg->option_names_case_sensitive = option_names_case_sensitive;
  cfg->read_only = FALSE;

  *cfgp = cfg;
  return SVN_NO_ERROR;
}
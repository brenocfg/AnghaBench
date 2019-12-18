#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct svn_config_t {int /*<<< orphan*/  sections; } ;
struct TYPE_3__ {int /*<<< orphan*/  options; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ cfg_section_t ;
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ cfg_option_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 void* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 

svn_error_t *
svn_config__write(svn_stream_t *stream,
                  const struct svn_config_t *cfg,
                  apr_pool_t *scratch_pool)
{
  apr_hash_index_t *section_i;
  apr_hash_index_t *options_i;
  apr_pool_t *section_pool = svn_pool_create(scratch_pool);
  apr_pool_t *options_pool = svn_pool_create(scratch_pool);

  for (section_i = apr_hash_first(scratch_pool, cfg->sections);
       section_i != NULL;
       section_i = apr_hash_next(section_i))
    {
      cfg_section_t *section = apr_hash_this_val(section_i);
      svn_pool_clear(section_pool);
      SVN_ERR(svn_stream_printf(stream, section_pool, "\n[%s]\n",
                                section->name));

      for (options_i = apr_hash_first(section_pool, section->options);
           options_i != NULL;
           options_i = apr_hash_next(options_i))
        {
          cfg_option_t *option = apr_hash_this_val(options_i);
          svn_pool_clear(options_pool);
          SVN_ERR(svn_stream_printf(stream, options_pool, "%s=%s\n",
                                    option->name, option->value));
        }
    }

  svn_pool_destroy(section_pool);
  svn_pool_destroy(options_pool);

  return SVN_NO_ERROR;
}
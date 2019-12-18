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
struct TYPE_7__ {TYPE_2__* tmp_value; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ svn_config_t ;
typedef  int /*<<< orphan*/  cfg_section_t ;
typedef  int /*<<< orphan*/  cfg_option_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_8__ {char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  expand_option_value (TYPE_1__*,int /*<<< orphan*/ *,char const*,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_option (TYPE_1__*,char const*,char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  make_string_from_option (char const**,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strchr (char const*,char) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_set (TYPE_2__*,char const*) ; 

void
svn_config_get(svn_config_t *cfg, const char **valuep,
               const char *section, const char *option,
               const char *default_value)
{
  *valuep = default_value;
  if (cfg)
    {
      cfg_section_t *sec;
      cfg_option_t *opt = find_option(cfg, section, option, &sec);
      if (opt != NULL)
        {
          make_string_from_option(valuep, cfg, sec, opt, NULL);
        }
      else
        /* before attempting to expand an option, check for the placeholder.
         * If there is none, there is no point in calling expand_option_value.
         */
        if (default_value && strchr(default_value, '%'))
          {
            apr_pool_t *tmp_pool = svn_pool_create(cfg->pool);
            const char *x_default;
            if (!expand_option_value(cfg, sec, default_value, &x_default,
                                     tmp_pool))
              {
                /* Recursive definitions are not supported.
                   Normalize the answer in that case. */
                *valuep = "";
              }
            else if (x_default)
              {
                svn_stringbuf_set(cfg->tmp_value, x_default);
                *valuep = cfg->tmp_value->data;
              }
            svn_pool_destroy(tmp_pool);
          }
    }
}
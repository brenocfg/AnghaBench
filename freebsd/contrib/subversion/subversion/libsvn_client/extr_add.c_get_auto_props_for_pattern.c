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
struct TYPE_4__ {char const* data; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_FNM_CASE_BLIND ; 
 scalar_t__ APR_FNM_NOMATCH ; 
 int /*<<< orphan*/  SVN_PROP_EXECUTABLE ; 
 int /*<<< orphan*/  SVN_PROP_MIME_TYPE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ apr_fnmatch (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_pool_get (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,TYPE_1__*) ; 
 TYPE_1__* svn_string_create_empty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_auto_props_for_pattern(apr_hash_t *properties,
                           const char **mimetype,
                           svn_boolean_t *have_executable,
                           const char *filename,
                           const char *pattern,
                           apr_hash_t *propvals,
                           apr_pool_t *scratch_pool)
{
  apr_hash_index_t *hi;

  /* check if filename matches and return if it doesn't */
  if (apr_fnmatch(pattern, filename,
                  APR_FNM_CASE_BLIND) == APR_FNM_NOMATCH)
    return;

  for (hi = apr_hash_first(scratch_pool, propvals);
       hi != NULL;
       hi = apr_hash_next(hi))
    {
      const char *propname = apr_hash_this_key(hi);
      const char *propval = apr_hash_this_val(hi);
      svn_string_t *propval_str =
        svn_string_create_empty(apr_hash_pool_get(properties));

      propval_str->data = propval;
      propval_str->len = strlen(propval);

      svn_hash_sets(properties, propname, propval_str);
      if (strcmp(propname, SVN_PROP_MIME_TYPE) == 0)
        *mimetype = propval;
      else if (strcmp(propname, SVN_PROP_EXECUTABLE) == 0)
        *have_executable = TRUE;
    }
}
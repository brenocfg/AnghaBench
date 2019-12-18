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
typedef  int /*<<< orphan*/  svn_string_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  const* value; } ;
typedef  TYPE_1__ svn_prop_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct revision_baton {int /*<<< orphan*/ * pool; int /*<<< orphan*/  rev_offset; struct parse_baton* pb; } ;
struct parse_baton {int /*<<< orphan*/  oldest_dumpstream_rev; int /*<<< orphan*/  rev_map; int /*<<< orphan*/  parent_dir; } ;
struct node_baton {int /*<<< orphan*/  prop_changes; struct revision_baton* rb; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_quick_wrap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * svn_repos__adjust_mergeinfo_property (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__normalize_prop (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__validate_prop (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
set_node_property(void *baton,
                  const char *name,
                  const svn_string_t *value)
{
  struct node_baton *nb = baton;
  struct revision_baton *rb = nb->rb;
  struct parse_baton *pb = rb->pb;
  apr_pool_t *pool = nb->rb->pool;
  svn_prop_t *prop;

  if (value && strcmp(name, SVN_PROP_MERGEINFO) == 0)
    {
      svn_string_t *new_value;
      svn_error_t *err;

      err = svn_repos__adjust_mergeinfo_property(&new_value, value,
                                                 pb->parent_dir,
                                                 pb->rev_map,
                                                 pb->oldest_dumpstream_rev,
                                                 rb->rev_offset,
                                                 NULL, NULL, /*notify*/
                                                 pool, pool);
      if (err)
        {
          return svn_error_quick_wrap(err,
                                      _("Invalid svn:mergeinfo value"));
        }

      value = new_value;
    }

  SVN_ERR(svn_repos__normalize_prop(&value, NULL, name, value, pool, pool));

  SVN_ERR(svn_repos__validate_prop(name, value, pool));

  prop = apr_palloc(nb->rb->pool, sizeof (*prop));
  prop->name = apr_pstrdup(pool, name);
  prop->value = value;
  svn_hash_sets(nb->prop_changes, prop->name, prop);

  return SVN_NO_ERROR;
}
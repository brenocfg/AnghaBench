#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
struct TYPE_5__ {int /*<<< orphan*/  warning_str; int /*<<< orphan*/  warning; } ;
typedef  TYPE_1__ svn_repos_notify_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct revision_baton {int /*<<< orphan*/  txn_root; int /*<<< orphan*/  rev_offset; scalar_t__ skipped; struct parse_baton* pb; } ;
struct parse_baton {scalar_t__ validate_props; int /*<<< orphan*/  notify_pool; int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  (* notify_func ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  oldest_dumpstream_rev; int /*<<< orphan*/  rev_map; int /*<<< orphan*/  parent_dir; } ;
struct node_baton {int /*<<< orphan*/  pool; int /*<<< orphan*/  path; struct revision_baton* rb; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * change_node_prop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_quick_wrap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_repos__adjust_mergeinfo_property (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_repos_notify_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_repos_notify_warning ; 
 int /*<<< orphan*/  svn_repos_notify_warning_invalid_mergeinfo ; 

__attribute__((used)) static svn_error_t *
set_node_property(void *baton,
                  const char *name,
                  const svn_string_t *value)
{
  struct node_baton *nb = baton;
  struct revision_baton *rb = nb->rb;
  struct parse_baton *pb = rb->pb;

  /* If we're skipping this revision, we're done here. */
  if (rb->skipped)
    return SVN_NO_ERROR;

  /* Adjust mergeinfo. If this fails, presumably because the mergeinfo
     property has an ill-formed value, then we must not fail to load
     the repository (at least if it's a simple load with no revision
     offset adjustments, path changes, etc.) so just warn and leave it
     as it is. */
  if (strcmp(name, SVN_PROP_MERGEINFO) == 0)
    {
      svn_string_t *new_value;
      svn_error_t *err;

      err = svn_repos__adjust_mergeinfo_property(&new_value, value,
                                                 pb->parent_dir,
                                                 pb->rev_map,
                                                 pb->oldest_dumpstream_rev,
                                                 rb->rev_offset,
                                                 pb->notify_func, pb->notify_baton,
                                                 nb->pool, pb->notify_pool);
      svn_pool_clear(pb->notify_pool);
      if (err)
        {
          if (pb->validate_props)
            {
              return svn_error_quick_wrap(
                       err,
                       _("Invalid svn:mergeinfo value"));
            }
          if (pb->notify_func)
            {
              svn_repos_notify_t *notify
                = svn_repos_notify_create(svn_repos_notify_warning,
                                          pb->notify_pool);

              notify->warning = svn_repos_notify_warning_invalid_mergeinfo;
              notify->warning_str = _("Invalid svn:mergeinfo value; "
                                      "leaving unchanged");
              pb->notify_func(pb->notify_baton, notify, pb->notify_pool);
              svn_pool_clear(pb->notify_pool);
            }
          svn_error_clear(err);
        }
      else
        {
          value = new_value;
        }
    }

  return change_node_prop(rb->txn_root, nb->path, name, value,
                          pb->validate_props, nb->pool);
}
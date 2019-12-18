#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_13__ {int /*<<< orphan*/ * dag_node_cache; } ;
typedef  TYPE_3__ svn_fs_x__data_t ;
typedef  int /*<<< orphan*/  svn_fs_x__dag_cache_t ;
typedef  int /*<<< orphan*/  svn_fs_x__change_set_t ;
struct TYPE_14__ {scalar_t__ rev; TYPE_1__* fs; } ;
typedef  TYPE_4__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
struct TYPE_15__ {int /*<<< orphan*/ * node; } ;
typedef  TYPE_5__ cache_entry_t ;
struct TYPE_11__ {TYPE_3__* fsap_data; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  auto_clear_dag_cache (int /*<<< orphan*/ *) ; 
 TYPE_5__* cache_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__ const*) ; 
 int /*<<< orphan*/ * cache_lookup_last_path (int /*<<< orphan*/ *,TYPE_2__ const*) ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  svn_fs_x__change_set_by_rev (scalar_t__) ; 
 int /*<<< orphan*/  svn_fs_x__dag_check_mutable (int /*<<< orphan*/ *) ; 
 char* svn_fs_x__dag_get_created_path (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_x__dag_get_revision (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
try_match_last_node(dag_node_t **node_p,
                    svn_fs_root_t *root,
                    const svn_string_t *path)
{
  svn_fs_x__data_t *ffd = root->fs->fsap_data;

  /* Optimistic lookup: if the last node returned from the cache applied to
     the same PATH, return it in NODE. */
  dag_node_t *node = cache_lookup_last_path(ffd->dag_node_cache, path);

  /* Did we get a bucket with a committed node? */
  if (node && !svn_fs_x__dag_check_mutable(node))
    {
      /* Get the path&rev pair at which this node was created.
         This is repository location for which this node is _known_ to be
         the right lookup result irrespective of how we found it. */
      const char *created_path
        = svn_fs_x__dag_get_created_path(node) + 1;
      svn_revnum_t revision = svn_fs_x__dag_get_revision(node);

      /* Is it an exact match? */
      if (   revision == root->rev
          && strlen(created_path) == path->len
          && memcmp(created_path, path->data, path->len) == 0)
        {
          svn_fs_x__dag_cache_t *cache = ffd->dag_node_cache;

          /* Insert NODE into the cache at a second location.
             In a fraction of all calls, the auto-cleanup may
             cause NODE to become invalid. */
          if (!auto_clear_dag_cache(cache))
            {
              /* Cache it under its full path@rev access path. */
              svn_fs_x__change_set_t change_set
                = svn_fs_x__change_set_by_rev(revision);
              cache_entry_t *bucket = cache_lookup(cache, change_set, path);
              bucket->node = node;

              *node_p = node;
              return SVN_NO_ERROR;
            }
        }
    }

  *node_p = NULL;
  return SVN_NO_ERROR;
}
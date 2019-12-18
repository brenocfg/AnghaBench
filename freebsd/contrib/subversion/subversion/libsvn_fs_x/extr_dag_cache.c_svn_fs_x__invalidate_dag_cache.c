#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* dag_node_cache; } ;
typedef  TYPE_2__ svn_fs_x__data_t ;
struct TYPE_10__ {TYPE_5__* buckets; } ;
typedef  TYPE_3__ svn_fs_x__dag_cache_t ;
typedef  scalar_t__ svn_fs_x__change_set_t ;
struct TYPE_11__ {TYPE_1__* fs; } ;
typedef  TYPE_4__ svn_fs_root_t ;
struct TYPE_12__ {scalar_t__ change_set; int /*<<< orphan*/ * node; int /*<<< orphan*/  path; } ;
typedef  TYPE_5__ cache_entry_t ;
typedef  size_t apr_size_t ;
struct TYPE_8__ {TYPE_2__* fsap_data; } ;

/* Variables and functions */
 size_t BUCKET_COUNT ; 
 scalar_t__ svn_fs_x__root_change_set (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_relpath_is_canonical (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_relpath_skip_ancestor (char const*,int /*<<< orphan*/ ) ; 

void
svn_fs_x__invalidate_dag_cache(svn_fs_root_t *root,
                               const char *path)
{
  svn_fs_x__data_t *ffd = root->fs->fsap_data;
  svn_fs_x__dag_cache_t *cache = ffd->dag_node_cache;
  svn_fs_x__change_set_t change_set = svn_fs_x__root_change_set(root);

  apr_size_t i;
  for (i = 0; i < BUCKET_COUNT; ++i)
    {
      cache_entry_t *bucket = &cache->buckets[i];
      if (bucket->change_set == change_set && bucket->node)
        {
          /* The call to svn_relpath_skip_ancestor() will require both
             parameters to be canonical.  Since we allow for non-canonical
             paths in our cache (unlikely to actually happen), we drop all
             such entries.
           */
          if (!svn_relpath_is_canonical(bucket->path)
              || svn_relpath_skip_ancestor(path + 1, bucket->path))
            bucket->node = NULL;
        }
    }
}
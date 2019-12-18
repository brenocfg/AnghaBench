#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_9__ {int /*<<< orphan*/  by_extension; int /*<<< orphan*/  file_histogram; int /*<<< orphan*/  file_rep_histogram; int /*<<< orphan*/  dir_histogram; int /*<<< orphan*/  dir_rep_histogram; int /*<<< orphan*/  file_prop_histogram; int /*<<< orphan*/  file_prop_rep_histogram; int /*<<< orphan*/  dir_prop_histogram; int /*<<< orphan*/  dir_prop_rep_histogram; int /*<<< orphan*/  unused_rep_histogram; int /*<<< orphan*/  added_node_size_histogram; int /*<<< orphan*/  added_rep_size_histogram; int /*<<< orphan*/  node_size_histogram; int /*<<< orphan*/  rep_size_histogram; TYPE_2__* largest_changes; } ;
typedef  TYPE_1__ svn_fs_fs__stats_t ;
struct TYPE_10__ {scalar_t__ min_size; int count; TYPE_3__** changes; } ;
typedef  TYPE_2__ svn_fs_fs__largest_changes_t ;
struct TYPE_11__ {scalar_t__ size; int /*<<< orphan*/  path; int /*<<< orphan*/  revision; } ;
typedef  TYPE_3__ svn_fs_fs__large_change_info_t ;
struct TYPE_12__ {int /*<<< orphan*/  rep_histogram; int /*<<< orphan*/  node_histogram; int /*<<< orphan*/  extension; } ;
typedef  TYPE_4__ svn_fs_fs__extension_info_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int rep_kind_t ;
typedef  scalar_t__ apr_uint64_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_HASH_KEY_STRING ; 
 int /*<<< orphan*/  add_to_histogram (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_4__* apr_hash_get (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_pool_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_4__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
#define  dir_property_rep 132 
#define  dir_rep 131 
#define  file_property_rep 130 
#define  file_rep 129 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  svn_stringbuf_set (int /*<<< orphan*/ ,char const*) ; 
#define  unused_rep 128 

__attribute__((used)) static void
add_change(svn_fs_fs__stats_t *stats,
           apr_uint64_t rep_size,
           apr_uint64_t expanded_size,
           svn_revnum_t revision,
           const char *path,
           rep_kind_t kind,
           svn_boolean_t plain_added)
{
  /* identify largest reps */
  if (rep_size >= stats->largest_changes->min_size)
    {
      apr_size_t i;
      svn_fs_fs__largest_changes_t *largest_changes = stats->largest_changes;
      svn_fs_fs__large_change_info_t *info
        = largest_changes->changes[largest_changes->count - 1];
      info->size = rep_size;
      info->revision = revision;
      svn_stringbuf_set(info->path, path);

      /* linear insertion but not too bad since count is low and insertions
       * near the end are more likely than close to front */
      for (i = largest_changes->count - 1; i > 0; --i)
        if (largest_changes->changes[i-1]->size >= rep_size)
          break;
        else
          largest_changes->changes[i] = largest_changes->changes[i-1];

      largest_changes->changes[i] = info;
      largest_changes->min_size
        = largest_changes->changes[largest_changes->count-1]->size;
    }

  /* global histograms */
  add_to_histogram(&stats->rep_size_histogram, rep_size);
  add_to_histogram(&stats->node_size_histogram, expanded_size);

  if (plain_added)
    {
      add_to_histogram(&stats->added_rep_size_histogram, rep_size);
      add_to_histogram(&stats->added_node_size_histogram, expanded_size);
    }

  /* specific histograms by type */
  switch (kind)
    {
      case unused_rep:
        add_to_histogram(&stats->unused_rep_histogram, rep_size);
        break;
      case dir_property_rep:
        add_to_histogram(&stats->dir_prop_rep_histogram, rep_size);
        add_to_histogram(&stats->dir_prop_histogram, expanded_size);
        break;
      case file_property_rep:
        add_to_histogram(&stats->file_prop_rep_histogram, rep_size);
        add_to_histogram(&stats->file_prop_histogram, expanded_size);
        break;
      case dir_rep:
        add_to_histogram(&stats->dir_rep_histogram, rep_size);
        add_to_histogram(&stats->dir_histogram, expanded_size);
        break;
      case file_rep:
        add_to_histogram(&stats->file_rep_histogram, rep_size);
        add_to_histogram(&stats->file_histogram, expanded_size);
        break;
    }

  /* by extension */
  if (kind == file_rep)
    {
      /* determine extension */
      svn_fs_fs__extension_info_t *info;
      const char * file_name = strrchr(path, '/');
      const char * extension = file_name ? strrchr(file_name, '.') : NULL;

      if (extension == NULL || extension == file_name + 1)
        extension = "(none)";

      /* get / auto-insert entry for this extension */
      info = apr_hash_get(stats->by_extension, extension, APR_HASH_KEY_STRING);
      if (info == NULL)
        {
          apr_pool_t *pool = apr_hash_pool_get(stats->by_extension);
          info = apr_pcalloc(pool, sizeof(*info));
          info->extension = apr_pstrdup(pool, extension);

          apr_hash_set(stats->by_extension, info->extension,
                       APR_HASH_KEY_STRING, info);
        }

      /* update per-extension histogram */
      add_to_histogram(&info->node_histogram, expanded_size);
      add_to_histogram(&info->rep_histogram, rep_size);
    }
}
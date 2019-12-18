#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_8__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct TYPE_9__ {int max_files_per_dir; } ;
typedef  TYPE_3__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int FALSE ; 
 char* PATH_MANIFEST ; 
 char* strchr (char*,char) ; 
 char* svn_dirent_join (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 char* svn_fs_fs__path_revprops_pack_shard (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__try_stringbuf_from_file (TYPE_1__**,int*,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_check_path (char*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_none ; 

svn_boolean_t
svn_fs_fs__packed_revprop_available(svn_boolean_t *missing,
                                    svn_fs_t *fs,
                                    svn_revnum_t revision,
                                    apr_pool_t *pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;
  svn_stringbuf_t *content = NULL;

  /* try to read the manifest file */
  const char *folder
    = svn_fs_fs__path_revprops_pack_shard(fs, revision, pool);
  const char *manifest_path = svn_dirent_join(folder, PATH_MANIFEST, pool);

  svn_error_t *err = svn_fs_fs__try_stringbuf_from_file(&content,
                                                        missing,
                                                        manifest_path,
                                                        FALSE,
                                                        pool);

  /* if the manifest cannot be read, consider the pack files inaccessible
   * even if the file itself exists. */
  if (err)
    {
      svn_error_clear(err);
      return FALSE;
    }

  if (*missing)
    return FALSE;

  /* parse manifest content until we find the entry for REVISION.
   * Revision 0 is never packed. */
  revision = revision < ffd->max_files_per_dir
           ? revision - 1
           : revision % ffd->max_files_per_dir;
  while (content->data)
    {
      char *next = strchr(content->data, '\n');
      if (next)
        {
          *next = 0;
          ++next;
        }

      if (revision-- == 0)
        {
          /* the respective pack file must exist (and be a file) */
          svn_node_kind_t kind;
          err = svn_io_check_path(svn_dirent_join(folder, content->data,
                                                  pool),
                                  &kind, pool);
          if (err)
            {
              svn_error_clear(err);
              return FALSE;
            }

          *missing = kind == svn_node_none;
          return kind == svn_node_file;
        }

      content->data = next;
    }

  return FALSE;
}
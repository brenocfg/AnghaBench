#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_13__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_2__ svn_fs_t ;
struct TYPE_14__ {int /*<<< orphan*/  number; } ;
typedef  TYPE_3__ svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PATH_NODE_ORIGINS_DIR ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/  SVN_HASH_TERMINATOR ; 
 int SVN_INT64_BUFFER_SIZE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* apr_hash_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  get_node_origins_from_file (TYPE_2__*,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn__ui64tobase36 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__ensure_dir_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_write2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/ * svn_io_file_rename2 (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_unique (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_string_compare (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
set_node_origins_for_file(svn_fs_t *fs,
                          const char *node_origins_path,
                          const svn_fs_fs__id_part_t *node_id,
                          svn_string_t *node_rev_id,
                          apr_pool_t *pool)
{
  const char *path_tmp;
  svn_stream_t *stream;
  apr_hash_t *origins_hash;
  svn_string_t *old_node_rev_id;

  /* the hash serialization functions require strings as keys */
  char node_id_ptr[SVN_INT64_BUFFER_SIZE];
  apr_size_t len = svn__ui64tobase36(node_id_ptr, node_id->number);

  SVN_ERR(svn_fs_fs__ensure_dir_exists(svn_dirent_join(fs->path,
                                                       PATH_NODE_ORIGINS_DIR,
                                                       pool),
                                       fs->path, pool));

  /* Read the previously existing origins (if any), and merge our
     update with it. */
  SVN_ERR(get_node_origins_from_file(fs, &origins_hash,
                                     node_origins_path, pool));
  if (! origins_hash)
    origins_hash = apr_hash_make(pool);

  old_node_rev_id = apr_hash_get(origins_hash, node_id_ptr, len);

  if (old_node_rev_id && !svn_string_compare(node_rev_id, old_node_rev_id))
    return svn_error_createf(SVN_ERR_FS_CORRUPT, NULL,
                             _("Node origin for '%s' exists with a different "
                               "value (%s) than what we were about to store "
                               "(%s)"),
                             node_id_ptr, old_node_rev_id->data,
                             node_rev_id->data);

  apr_hash_set(origins_hash, node_id_ptr, len, node_rev_id);

  /* Sure, there's a race condition here.  Two processes could be
     trying to add different cache elements to the same file at the
     same time, and the entries added by the first one to write will
     be lost.  But this is just a cache of reconstructible data, so
     we'll accept this problem in return for not having to deal with
     locking overhead. */

  /* Create a temporary file, write out our hash, and close the file. */
  SVN_ERR(svn_stream_open_unique(&stream, &path_tmp,
                                 svn_dirent_dirname(node_origins_path, pool),
                                 svn_io_file_del_none, pool, pool));
  SVN_ERR(svn_hash_write2(origins_hash, stream, SVN_HASH_TERMINATOR, pool));
  SVN_ERR(svn_stream_close(stream));

  /* Rename the temp file as the real destination */
  return svn_io_file_rename2(path_tmp, node_origins_path, FALSE, pool);
}
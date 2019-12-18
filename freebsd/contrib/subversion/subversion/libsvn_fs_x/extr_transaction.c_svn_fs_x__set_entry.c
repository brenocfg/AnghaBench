#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  void* svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
struct TYPE_20__ {int /*<<< orphan*/  number; int /*<<< orphan*/  change_set; } ;
struct TYPE_22__ {TYPE_1__ id; } ;
typedef  TYPE_3__ svn_fs_x__representation_t ;
struct TYPE_23__ {TYPE_3__* data_rep; int /*<<< orphan*/  noderev_id; } ;
typedef  TYPE_4__ svn_fs_x__noderev_t ;
typedef  int /*<<< orphan*/  svn_fs_x__id_t ;
struct TYPE_24__ {char const* name; void* kind; int /*<<< orphan*/  id; } ;
typedef  TYPE_5__ svn_fs_x__dirent_t ;
struct TYPE_25__ {scalar_t__ txn_filesize; int /*<<< orphan*/ * entries; } ;
typedef  TYPE_6__ svn_fs_x__dir_data_t ;
struct TYPE_26__ {int /*<<< orphan*/  dir_cache; } ;
typedef  TYPE_7__ svn_fs_x__data_t ;
struct TYPE_27__ {TYPE_7__* fsap_data; } ;
typedef  TYPE_8__ svn_fs_t ;
typedef  scalar_t__ svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_28__ {char const* name; TYPE_2__* new_entry; scalar_t__ txn_filesize; } ;
typedef  TYPE_9__ replace_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_21__ {char const* name; int /*<<< orphan*/  id; void* kind; } ;

/* Variables and functions */
 int APR_APPEND ; 
 int APR_BUFFERED ; 
 int APR_CREATE ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_WRITE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_FS_X__ITEM_INDEX_UNUSED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_cache__get_partial (void**,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__set (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__set_partial (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__change_set_by_txn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__extract_dir_filesize ; 
 int /*<<< orphan*/  svn_fs_x__id_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__is_txn (int /*<<< orphan*/ ) ; 
 char* svn_fs_x__path_txn_node_children (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__put_node_revision (TYPE_8__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__rep_contents_dir (int /*<<< orphan*/ **,TYPE_8__*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__replace_dir_entry ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_size_get (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_aprfile2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unparse_dir_entries (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unparse_dir_entry (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__set_entry(svn_fs_t *fs,
                    svn_fs_x__txn_id_t txn_id,
                    svn_fs_x__noderev_t *parent_noderev,
                    const char *name,
                    const svn_fs_x__id_t *id,
                    svn_node_kind_t kind,
                    apr_pool_t *result_pool,
                    apr_pool_t *scratch_pool)
{
  svn_fs_x__representation_t *rep = parent_noderev->data_rep;
  const char *filename
    = svn_fs_x__path_txn_node_children(fs, &parent_noderev->noderev_id,
                                       scratch_pool, scratch_pool);
  apr_file_t *file;
  svn_stream_t *out;
  svn_filesize_t filesize;
  svn_fs_x__data_t *ffd = fs->fsap_data;
  apr_pool_t *subpool = svn_pool_create(scratch_pool);
  const svn_fs_x__id_t *key = &(parent_noderev->noderev_id);
  svn_fs_x__dirent_t entry;

  if (!rep || !svn_fs_x__is_txn(rep->id.change_set))
    {
      apr_array_header_t *entries;
      svn_fs_x__dir_data_t dir_data;

      /* Before we can modify the directory, we need to dump its old
         contents into a mutable representation file. */
      SVN_ERR(svn_fs_x__rep_contents_dir(&entries, fs, parent_noderev,
                                         subpool, subpool));
      SVN_ERR(svn_io_file_open(&file, filename,
                               APR_WRITE | APR_CREATE | APR_BUFFERED,
                               APR_OS_DEFAULT, scratch_pool));
      out = svn_stream_from_aprfile2(file, TRUE, scratch_pool);
      SVN_ERR(unparse_dir_entries(entries, out, subpool));

      /* Provide the parent with a data rep if it had none before
         (directories so far empty). */
      if (!rep)
        {
          rep = apr_pcalloc(result_pool, sizeof(*rep));
          parent_noderev->data_rep = rep;
        }

      /* Mark the node-rev's data rep as mutable. */
      rep->id.change_set = svn_fs_x__change_set_by_txn(txn_id);
      rep->id.number = SVN_FS_X__ITEM_INDEX_UNUSED;

      /* Save noderev to disk. */
      SVN_ERR(svn_fs_x__put_node_revision(fs, parent_noderev, subpool));

      /* Immediately populate the txn dir cache to avoid re-reading
       * the file we just wrote. */

      /* Flush APR buffers. */
      SVN_ERR(svn_io_file_flush(file, subpool));

      /* Obtain final file size to update txn_dir_cache. */
      SVN_ERR(svn_io_file_size_get(&filesize, file, subpool));

      /* Store in the cache. */
      dir_data.entries = entries;
      dir_data.txn_filesize = filesize;
      SVN_ERR(svn_cache__set(ffd->dir_cache, key, &dir_data, subpool));

      svn_pool_clear(subpool);
    }
  else
    {
      svn_boolean_t found;
      svn_filesize_t cached_filesize;

      /* The directory rep is already mutable, so just open it for append. */
      SVN_ERR(svn_io_file_open(&file, filename, APR_WRITE | APR_APPEND,
                               APR_OS_DEFAULT, subpool));
      out = svn_stream_from_aprfile2(file, TRUE, subpool);

      /* If the cache contents is stale, drop it.
       *
       * Note that the directory file is append-only, i.e. if the size
       * did not change, the contents didn't either. */

      /* Get the file size that corresponds to the cached contents
       * (if any). */
      SVN_ERR(svn_cache__get_partial((void **)&cached_filesize, &found,
                                     ffd->dir_cache, key,
                                     svn_fs_x__extract_dir_filesize,
                                     NULL, subpool));

      /* File size info still matches?
       * If not, we need to drop the cache entry. */
      if (found)
        {
          SVN_ERR(svn_io_file_size_get(&filesize, file, subpool));

          if (cached_filesize != filesize)
            SVN_ERR(svn_cache__set(ffd->dir_cache, key, NULL, subpool));
        }
    }

  /* Append an incremental hash entry for the entry change.
     A deletion is represented by an "unused" noderev-id. */
  if (id)
    entry.id = *id;
  else
    svn_fs_x__id_reset(&entry.id);

  entry.name = name;
  entry.kind = kind;

  SVN_ERR(unparse_dir_entry(&entry, out, subpool));

  /* Flush APR buffers. */
  SVN_ERR(svn_io_file_flush(file, subpool));

  /* Obtain final file size to update txn_dir_cache. */
  SVN_ERR(svn_io_file_size_get(&filesize, file, subpool));

  /* Close file. */
  SVN_ERR(svn_io_file_close(file, subpool));
  svn_pool_clear(subpool);

  /* update directory cache */
    {
      /* build parameters: name, new entry, new file size  */
      replace_baton_t baton;

      baton.name = name;
      baton.new_entry = NULL;
      baton.txn_filesize = filesize;

      if (id)
        {
          baton.new_entry = apr_pcalloc(subpool, sizeof(*baton.new_entry));
          baton.new_entry->name = name;
          baton.new_entry->kind = kind;
          baton.new_entry->id = *id;
        }

      /* actually update the cached directory (if cached) */
      SVN_ERR(svn_cache__set_partial(ffd->dir_cache, key,
                                     svn_fs_x__replace_dir_entry, &baton,
                                     subpool));
    }

  svn_pool_destroy(subpool);
  return SVN_NO_ERROR;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
struct TYPE_20__ {int /*<<< orphan*/  file; int /*<<< orphan*/  stream; } ;
typedef  TYPE_3__ svn_fs_fs__revision_file_t ;
struct TYPE_21__ {scalar_t__ type; } ;
typedef  TYPE_4__ svn_fs_fs__rep_header_t ;
struct TYPE_22__ {scalar_t__ revision; int /*<<< orphan*/  number; } ;
typedef  TYPE_5__ svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct recover_read_from_file_baton {int /*<<< orphan*/  remaining; int /*<<< orphan*/ * pool; int /*<<< orphan*/  stream; } ;
struct TYPE_23__ {scalar_t__ kind; int /*<<< orphan*/  id; TYPE_1__* data_rep; } ;
typedef  TYPE_6__ node_revision_t ;
typedef  scalar_t__ apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_18__ {scalar_t__ revision; int /*<<< orphan*/  expanded_size; int /*<<< orphan*/  item_index; } ;
struct TYPE_17__ {scalar_t__ number; } ;
struct TYPE_16__ {scalar_t__ number; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SET ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/  SVN_FS_FS__KIND_DIR ; 
 int /*<<< orphan*/  SVN_FS_FS__KIND_FILE ; 
 int /*<<< orphan*/  SVN_HASH_TERMINATOR ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 TYPE_2__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_handler_recover ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 char* svn_cstring_tokenize (char*,char**) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_quick_wrapf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_13__* svn_fs_fs__id_copy_id (int /*<<< orphan*/  const*) ; 
 TYPE_12__* svn_fs_fs__id_node_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * svn_fs_fs__id_parse (int /*<<< orphan*/  const**,char*,int /*<<< orphan*/ *) ; 
 TYPE_5__* svn_fs_fs__id_rev_item (int /*<<< orphan*/  const*) ; 
 TYPE_2__* svn_fs_fs__id_unparse (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__item_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__read_noderev (TYPE_6__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__read_rep_header (TYPE_4__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_fs__rep_plain ; 
 int /*<<< orphan*/ * svn_hash_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_file_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_create (struct recover_read_from_file_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
recover_find_max_ids(svn_fs_t *fs,
                     svn_revnum_t rev,
                     svn_fs_fs__revision_file_t *rev_file,
                     apr_off_t offset,
                     apr_uint64_t *max_node_id,
                     apr_uint64_t *max_copy_id,
                     apr_pool_t *pool)
{
  svn_fs_fs__rep_header_t *header;
  struct recover_read_from_file_baton baton;
  svn_stream_t *stream;
  apr_hash_t *entries;
  apr_hash_index_t *hi;
  apr_pool_t *iterpool;
  node_revision_t *noderev;
  svn_error_t *err;

  baton.stream = rev_file->stream;
  SVN_ERR(svn_io_file_seek(rev_file->file, APR_SET, &offset, pool));
  SVN_ERR(svn_fs_fs__read_noderev(&noderev, baton.stream, pool, pool));

  /* Check that this is a directory.  It should be. */
  if (noderev->kind != svn_node_dir)
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Recovery encountered a non-directory node"));

  /* Get the data location.  No data location indicates an empty directory. */
  if (!noderev->data_rep)
    return SVN_NO_ERROR;

  /* If the directory's data representation wasn't changed in this revision,
     we've already scanned the directory's contents for noderevs, so we don't
     need to again.  This will occur if a property is changed on a directory
     without changing the directory's contents. */
  if (noderev->data_rep->revision != rev)
    return SVN_NO_ERROR;

  /* We could use get_dir_contents(), but this is much cheaper.  It does
     rely on directory entries being stored as PLAIN reps, though. */
  SVN_ERR(svn_fs_fs__item_offset(&offset, fs, rev_file, rev, NULL,
                                 noderev->data_rep->item_index, pool));
  SVN_ERR(svn_io_file_seek(rev_file->file, APR_SET, &offset, pool));
  SVN_ERR(svn_fs_fs__read_rep_header(&header, baton.stream, pool, pool));
  if (header->type != svn_fs_fs__rep_plain)
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Recovery encountered a deltified directory "
                              "representation"));

  /* Now create a stream that's allowed to read only as much data as is
     stored in the representation.  Note that this is a directory, i.e.
     represented using the hash format on disk and can never have 0 length. */
  baton.pool = pool;
  baton.remaining = noderev->data_rep->expanded_size;
  stream = svn_stream_create(&baton, pool);
  svn_stream_set_read2(stream, NULL /* only full read support */,
                       read_handler_recover);

  /* Now read the entries from that stream. */
  entries = apr_hash_make(pool);
  err = svn_hash_read2(entries, stream, SVN_HASH_TERMINATOR, pool);
  if (err)
    {
      svn_string_t *id_str = svn_fs_fs__id_unparse(noderev->id, pool);

      err = svn_error_compose_create(err, svn_stream_close(stream));
      return svn_error_quick_wrapf(err,
                _("malformed representation for node-revision '%s'"),
                id_str->data);
    }
  SVN_ERR(svn_stream_close(stream));

  /* Now check each of the entries in our directory to find new node and
     copy ids, and recurse into new subdirectories. */
  iterpool = svn_pool_create(pool);
  for (hi = apr_hash_first(pool, entries); hi; hi = apr_hash_next(hi))
    {
      char *str_val;
      char *str;
      svn_node_kind_t kind;
      const svn_fs_id_t *id;
      const svn_fs_fs__id_part_t *rev_item;
      apr_uint64_t node_id, copy_id;
      apr_off_t child_dir_offset;
      const svn_string_t *path = apr_hash_this_val(hi);

      svn_pool_clear(iterpool);

      str_val = apr_pstrdup(iterpool, path->data);

      str = svn_cstring_tokenize(" ", &str_val);
      if (str == NULL)
        return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                                _("Directory entry corrupt"));

      if (strcmp(str, SVN_FS_FS__KIND_FILE) == 0)
        kind = svn_node_file;
      else if (strcmp(str, SVN_FS_FS__KIND_DIR) == 0)
        kind = svn_node_dir;
      else
        {
          return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                                  _("Directory entry corrupt"));
        }

      str = svn_cstring_tokenize(" ", &str_val);
      if (str == NULL)
        return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                                _("Directory entry corrupt"));

      SVN_ERR(svn_fs_fs__id_parse(&id, str, iterpool));

      rev_item = svn_fs_fs__id_rev_item(id);
      if (rev_item->revision != rev)
        {
          /* If the node wasn't modified in this revision, we've already
             checked the node and copy id. */
          continue;
        }

      node_id = svn_fs_fs__id_node_id(id)->number;
      copy_id = svn_fs_fs__id_copy_id(id)->number;

      if (node_id > *max_node_id)
        *max_node_id = node_id;
      if (copy_id > *max_copy_id)
        *max_copy_id = copy_id;

      if (kind == svn_node_file)
        continue;

      SVN_ERR(svn_fs_fs__item_offset(&child_dir_offset, fs,
                                     rev_file, rev, NULL, rev_item->number,
                                     iterpool));
      SVN_ERR(recover_find_max_ids(fs, rev, rev_file, child_dir_offset,
                                   max_node_id, max_copy_id, iterpool));
    }
  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}
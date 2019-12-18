#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_8__ {TYPE_4__* data_rep; int /*<<< orphan*/  noderev_id; } ;
typedef  TYPE_2__ svn_fs_x__noderev_t ;
typedef  int /*<<< orphan*/  svn_fs_x__id_t ;
typedef  int /*<<< orphan*/  svn_fs_x__dirent_t ;
struct TYPE_9__ {int /*<<< orphan*/  entries; scalar_t__ txn_filesize; } ;
typedef  TYPE_3__ svn_fs_x__dir_data_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;
struct TYPE_7__ {int /*<<< orphan*/  change_set; } ;
struct TYPE_10__ {scalar_t__ expanded_size; TYPE_1__ id; } ;

/* Variables and functions */
 int APR_BUFFERED ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_READ ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_INVALID_FILESIZE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apr_array_make (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_dir_entries (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_contents (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__is_revision (int /*<<< orphan*/ ) ; 
 char* svn_fs_x__path_txn_node_children (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_size_get (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_aprfile2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_from_stream (int /*<<< orphan*/ **,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_dir_contents(svn_fs_x__dir_data_t *dir,
                 svn_fs_t *fs,
                 svn_fs_x__noderev_t *noderev,
                 apr_pool_t *result_pool,
                 apr_pool_t *scratch_pool)
{
  svn_stream_t *contents;
  const svn_fs_x__id_t *id = &noderev->noderev_id;
  apr_size_t len;
  svn_stringbuf_t *text;
  svn_boolean_t incremental;

  /* Initialize the result. */
  dir->txn_filesize = SVN_INVALID_FILESIZE;

  /* Read dir contents - unless there is none in which case we are done. */
  if (noderev->data_rep
      && ! svn_fs_x__is_revision(noderev->data_rep->id.change_set))
    {
      /* Get location & current size of the directory representation. */
      const char *filename;
      apr_file_t *file;

      filename = svn_fs_x__path_txn_node_children(fs, id, scratch_pool,
                                                  scratch_pool);

      /* The representation is mutable.  Read the old directory
         contents from the mutable children file, followed by the
         changes we've made in this transaction. */
      SVN_ERR(svn_io_file_open(&file, filename, APR_READ | APR_BUFFERED,
                               APR_OS_DEFAULT, scratch_pool));

      /* Obtain txn children file size. */
      SVN_ERR(svn_io_file_size_get(&dir->txn_filesize, file, scratch_pool));
      len = (apr_size_t)dir->txn_filesize;

      /* Finally, provide stream access to FILE. */
      contents = svn_stream_from_aprfile2(file, FALSE, scratch_pool);
      incremental = TRUE;
    }
  else if (noderev->data_rep)
    {
      /* The representation is immutable.  Read it normally. */
      len = noderev->data_rep->expanded_size;
      SVN_ERR(svn_fs_x__get_contents(&contents, fs, noderev->data_rep,
                                     FALSE, scratch_pool));
      incremental = FALSE;
    }
  else
    {
      /* Empty representation == empty directory. */
      dir->entries = apr_array_make(result_pool, 0,
                                    sizeof(svn_fs_x__dirent_t *));
      return SVN_NO_ERROR;
    }

  /* Read the whole stream contents into a single buffer.
   * Due to our LEN hint, no allocation overhead occurs.
   *
   * Also, a large portion of TEXT will be file / dir names which we
   * directly reference from DIR->ENTRIES instead of copying them.
   * Hence, we need to use the RESULT_POOL here. */
  SVN_ERR(svn_stringbuf_from_stream(&text, contents, len, result_pool));
  SVN_ERR(svn_stream_close(contents));

  /* de-serialize hash */
  SVN_ERR(parse_dir_entries(&dir->entries, text, incremental, id,
                            result_pool, scratch_pool));

  return SVN_NO_ERROR;
}
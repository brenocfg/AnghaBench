#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_13__ {TYPE_10__* rev_file; scalar_t__ offset; } ;
typedef  TYPE_2__ revision_info_t ;
typedef  int /*<<< orphan*/  query_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;
struct TYPE_11__ {int /*<<< orphan*/  stream; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SET ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (TYPE_10__*) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_io_file_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_readline (int /*<<< orphan*/ ,TYPE_1__**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbyte (TYPE_1__*,char) ; 
 int /*<<< orphan*/  svn_stringbuf_appendstr (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_phsy_noderev(svn_stringbuf_t **noderev,
                  query_t *query,
                  apr_off_t offset,
                  revision_info_t *revision_info,
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  svn_stringbuf_t *noderev_str = svn_stringbuf_create_empty(result_pool);
  svn_stringbuf_t *line;
  svn_boolean_t eof;

  apr_pool_t *iterpool = svn_pool_create(scratch_pool);

  /* Navigate the file stream to the start of noderev. */
  SVN_ERR_ASSERT(revision_info->rev_file);

  offset += revision_info->offset;
  SVN_ERR(svn_io_file_seek(revision_info->rev_file->file, APR_SET,
                           &offset, scratch_pool));

  /* Read it (terminated by an empty line) */
  do
    {
      svn_pool_clear(iterpool);

      SVN_ERR(svn_stream_readline(revision_info->rev_file->stream, &line,
                                  "\n", &eof, iterpool));
      svn_stringbuf_appendstr(noderev_str, line);
      svn_stringbuf_appendbyte(noderev_str, '\n');
    }
  while (line->len > 0 && !eof);

  /* Return the result. */
  *noderev = noderev_str;

  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}
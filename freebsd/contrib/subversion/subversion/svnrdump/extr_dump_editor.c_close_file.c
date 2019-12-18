#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_repos__dumpfile_headers_t ;
typedef  int /*<<< orphan*/  svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct file_baton {char const* base_checksum; scalar_t__ dump_text; int /*<<< orphan*/  deleted_props; int /*<<< orphan*/  props; scalar_t__ dump_props; int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/  copyfrom_path; int /*<<< orphan*/  is_copy; int /*<<< orphan*/  action; int /*<<< orphan*/  repos_relpath; struct dump_edit_baton* eb; } ;
struct dump_edit_baton {int /*<<< orphan*/  stream; int /*<<< orphan*/  delta_file; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SET ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_TEXT_CONTENT_MD5 ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_TEXT_DELTA ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_TEXT_DELTA_BASE_MD5 ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apr_hash_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_node (int /*<<< orphan*/ **,struct dump_edit_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct file_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_pending_dir (struct dump_edit_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_props_content (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_size_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_trunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__dump_node_record (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__dumpfile_header_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_copy3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_aprfile2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_puts (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static svn_error_t *
close_file(void *file_baton,
           const char *text_checksum,
           apr_pool_t *pool)
{
  struct file_baton *fb = file_baton;
  struct dump_edit_baton *eb = fb->eb;
  svn_filesize_t text_content_length = 0;
  svn_stringbuf_t *propstring = NULL;
  svn_repos__dumpfile_headers_t *headers;

  SVN_ERR(dump_pending_dir(eb, pool));

  /* Start dumping this node, by collecting some basic headers for it. */
  SVN_ERR(dump_node(&headers, eb, fb->repos_relpath, NULL, fb,
                    fb->action, fb->is_copy, fb->copyfrom_path,
                    fb->copyfrom_rev, pool));

  /* Some pending properties to dump?  We'll dump just the headers for
     now, then dump the actual propchange content only after dumping
     the text headers too (if present). */
  if (fb->dump_props)
    {
      SVN_ERR(get_props_content(headers, &propstring,
                                fb->props, fb->deleted_props,
                                pool, pool));
    }

  /* Dump the text headers */
  if (fb->dump_text)
    {
      /* Text-delta: true */
      svn_repos__dumpfile_header_push(
        headers, SVN_REPOS_DUMPFILE_TEXT_DELTA, "true");

      SVN_ERR(svn_io_file_size_get(&text_content_length, eb->delta_file,
                                   pool));

      if (fb->base_checksum)
        /* Text-delta-base-md5: */
        svn_repos__dumpfile_header_push(
          headers, SVN_REPOS_DUMPFILE_TEXT_DELTA_BASE_MD5, fb->base_checksum);

      /* Text-content-md5: 82705804337e04dcd0e586bfa2389a7f */
      svn_repos__dumpfile_header_push(
        headers, SVN_REPOS_DUMPFILE_TEXT_CONTENT_MD5, text_checksum);
    }

  /* Dump the headers and props now */
  SVN_ERR(svn_repos__dump_node_record(eb->stream, headers, propstring,
                                      fb->dump_text, text_content_length,
                                      FALSE /*content_length_always*/,
                                      pool));

  if (fb->dump_props)
    {
      /* Cleanup */
      fb->dump_props = FALSE;
      apr_hash_clear(fb->props);
      apr_hash_clear(fb->deleted_props);
    }

  /* Dump the text */
  if (fb->dump_text)
    {
      /* Seek to the beginning of the delta file, map it to a stream,
         and copy the stream to eb->stream. Then close the stream and
         truncate the file so we can reuse it for the next textdelta
         application. Note that the file isn't created, opened or
         closed here */
      svn_stream_t *delta_filestream;
      apr_off_t offset = 0;

      SVN_ERR(svn_io_file_seek(eb->delta_file, APR_SET, &offset, pool));
      delta_filestream = svn_stream_from_aprfile2(eb->delta_file, TRUE, pool);
      SVN_ERR(svn_stream_copy3(delta_filestream, eb->stream, NULL, NULL, pool));

      /* Cleanup */
      SVN_ERR(svn_stream_close(delta_filestream));
      SVN_ERR(svn_io_file_trunc(eb->delta_file, 0, pool));
    }

  /* Write a couple of blank lines for matching output with `svnadmin
     dump` */
  SVN_ERR(svn_stream_puts(eb->stream, "\n\n"));

  return SVN_NO_ERROR;
}
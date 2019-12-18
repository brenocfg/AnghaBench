#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* close_revision ) (void*) ;int /*<<< orphan*/  (* close_node ) (void*) ;int /*<<< orphan*/  (* remove_node_props ) (void*) ;int /*<<< orphan*/  (* uuid_record ) (char const*,void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* new_node_record ) (void**,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* new_revision_record ) (void**,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* magic_header_record ) (int,void*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ svn_repos_parse_fns3_t ;
typedef  scalar_t__ svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  (* svn_cancel_func_t ) (void*) ;
typedef  int svn_boolean_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_STREAM_MALFORMED_DATA ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_CONTENT_LENGTH ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_MAGIC_HEADER ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_NODE_KIND ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_NODE_PATH ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_PROP_CONTENT_LENGTH ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_PROP_DELTA ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_REVISION_NUMBER ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_TEXT_CONTENT_LENGTH ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_TEXT_DELTA ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_UUID ; 
 scalar_t__ SVN__STREAM_CHUNK_SIZE ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_palloc (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__* complete_vtable (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_format_version (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_property_block (int /*<<< orphan*/ *,scalar_t__,TYPE_2__ const*,void*,void*,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_text_block (int /*<<< orphan*/ *,scalar_t__,int,TYPE_2__ const*,void*,char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_header_block (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * stream_ran_dry () ; 
 int /*<<< orphan*/  stub1 (int,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 int /*<<< orphan*/  stub3 (void**,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (void**,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (char const*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (void*) ; 
 int /*<<< orphan*/  stub7 (void*) ; 
 int /*<<< orphan*/  stub8 (void*) ; 
 scalar_t__ svn__atoui64 (char const*) ; 
 int /*<<< orphan*/  svn_cstring_atoi (int*,char const*) ; 
 scalar_t__ svn_ctype_isspace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_read_full (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  svn_stream_readline (int /*<<< orphan*/ *,TYPE_1__**,char*,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_stringbuf_isempty (TYPE_1__*) ; 

svn_error_t *
svn_repos_parse_dumpstream3(svn_stream_t *stream,
                            const svn_repos_parse_fns3_t *parse_fns,
                            void *parse_baton,
                            svn_boolean_t deltas_are_text,
                            svn_cancel_func_t cancel_func,
                            void *cancel_baton,
                            apr_pool_t *pool)
{
  svn_boolean_t eof;
  svn_stringbuf_t *linebuf;
  void *rev_baton = NULL;
  char *buffer = apr_palloc(pool, SVN__STREAM_CHUNK_SIZE);
  apr_size_t buflen = SVN__STREAM_CHUNK_SIZE;
  apr_pool_t *linepool = svn_pool_create(pool);
  apr_pool_t *revpool = svn_pool_create(pool);
  apr_pool_t *nodepool = svn_pool_create(pool);
  int version;

  /* Make sure we can blindly invoke callbacks. */
  parse_fns = complete_vtable(parse_fns, pool);

  /* Start parsing process. */
  SVN_ERR(svn_stream_readline(stream, &linebuf, "\n", &eof, linepool));
  if (eof)
    return stream_ran_dry();

  /* The first two lines of the stream are the dumpfile-format version
     number, and a blank line.  To preserve backward compatibility,
     don't assume the existence of newer parser-vtable functions. */
  SVN_ERR(parse_format_version(&version, linebuf->data));
  if (parse_fns->magic_header_record != NULL)
    SVN_ERR(parse_fns->magic_header_record(version, parse_baton, pool));

  /* A dumpfile "record" is defined to be a header-block of
     rfc822-style headers, possibly followed by a content-block.

       - A header-block is always terminated by a single blank line (\n\n)

       - We know whether the record has a content-block by looking for
         a 'Content-length:' header.  The content-block will always be
         of a specific length, plus an extra newline.

     Once a record is fully sucked from the stream, an indeterminate
     number of blank lines (or lines that begin with whitespace) may
     follow before the next record (or the end of the stream.)
  */

  while (1)
    {
      apr_hash_t *headers;
      void *node_baton;
      svn_boolean_t found_node = FALSE;
      svn_boolean_t old_v1_with_cl = FALSE;
      const char *content_length;
      const char *prop_cl;
      const char *text_cl;
      const char *value;
      svn_filesize_t actual_prop_length;

      /* Clear our per-line pool. */
      svn_pool_clear(linepool);

      /* Check for cancellation. */
      if (cancel_func)
        SVN_ERR(cancel_func(cancel_baton));

      /* Keep reading blank lines until we discover a new record, or until
         the stream runs out. */
      SVN_ERR(svn_stream_readline(stream, &linebuf, "\n", &eof, linepool));

      if (eof)
        {
          if (svn_stringbuf_isempty(linebuf))
            break;   /* end of stream, go home. */
          else
            return stream_ran_dry();
        }

      if ((linebuf->len == 0) || (svn_ctype_isspace(linebuf->data[0])))
        continue; /* empty line ... loop */

      /*** Found the beginning of a new record. ***/

      /* The last line we read better be a header of some sort.
         Read the whole header-block into a hash. */
      SVN_ERR(read_header_block(stream, linebuf, &headers, linepool));

      /*** Handle the various header blocks. ***/

      /* Is this a revision record? */
      if (svn_hash_gets(headers, SVN_REPOS_DUMPFILE_REVISION_NUMBER))
        {
          /* If we already have a rev_baton open, we need to close it
             and clear the per-revision subpool. */
          if (rev_baton != NULL)
            {
              SVN_ERR(parse_fns->close_revision(rev_baton));
              svn_pool_clear(revpool);
            }

          SVN_ERR(parse_fns->new_revision_record(&rev_baton,
                                                 headers, parse_baton,
                                                 revpool));
        }
      /* Or is this, perhaps, a node record? */
      else if (svn_hash_gets(headers, SVN_REPOS_DUMPFILE_NODE_PATH))
        {
          SVN_ERR(parse_fns->new_node_record(&node_baton,
                                             headers,
                                             rev_baton,
                                             nodepool));
          found_node = TRUE;
        }
      /* Or is this the repos UUID? */
      else if ((value = svn_hash_gets(headers, SVN_REPOS_DUMPFILE_UUID)))
        {
          SVN_ERR(parse_fns->uuid_record(value, parse_baton, pool));
        }
      /* Or perhaps a dumpfile format? */
      /* ### TODO: use parse_format_version */
      else if ((value = svn_hash_gets(headers,
                                      SVN_REPOS_DUMPFILE_MAGIC_HEADER)))
        {
          /* ### someday, switch modes of operation here. */
          SVN_ERR(svn_cstring_atoi(&version, value));
        }
      /* Or is this bogosity?! */
      else
        {
          /* What the heck is this record?!? */
          return svn_error_create(SVN_ERR_STREAM_MALFORMED_DATA, NULL,
                                  _("Unrecognized record type in stream"));
        }

      /* Need 3 values below to determine v1 dump type

         Old (pre 0.14?) v1 dumps don't have Prop-content-length
         and Text-content-length fields, but always have a properties
         block in a block with Content-Length > 0 */

      content_length = svn_hash_gets(headers,
                                     SVN_REPOS_DUMPFILE_CONTENT_LENGTH);
      prop_cl = svn_hash_gets(headers, SVN_REPOS_DUMPFILE_PROP_CONTENT_LENGTH);
      text_cl = svn_hash_gets(headers, SVN_REPOS_DUMPFILE_TEXT_CONTENT_LENGTH);
      old_v1_with_cl =
        version == 1 && content_length && ! prop_cl && ! text_cl;

      /* Is there a props content-block to parse? */
      if (prop_cl || old_v1_with_cl)
        {
          const char *delta = svn_hash_gets(headers,
                                            SVN_REPOS_DUMPFILE_PROP_DELTA);
          svn_boolean_t is_delta = (delta && strcmp(delta, "true") == 0);

          /* First, remove all node properties, unless this is a delta
             property block. */
          if (found_node && !is_delta)
            SVN_ERR(parse_fns->remove_node_props(node_baton));

          SVN_ERR(parse_property_block
                  (stream,
                   svn__atoui64(prop_cl ? prop_cl : content_length),
                   parse_fns,
                   found_node ? node_baton : rev_baton,
                   parse_baton,
                   found_node,
                   &actual_prop_length,
                   found_node ? nodepool : revpool));
        }

      /* Is there a text content-block to parse? */
      if (text_cl)
        {
          const char *delta = svn_hash_gets(headers,
                                            SVN_REPOS_DUMPFILE_TEXT_DELTA);
          svn_boolean_t is_delta = FALSE;
          if (! deltas_are_text)
            is_delta = (delta && strcmp(delta, "true") == 0);

          SVN_ERR(parse_text_block(stream,
                                   svn__atoui64(text_cl),
                                   is_delta,
                                   parse_fns,
                                   found_node ? node_baton : rev_baton,
                                   buffer,
                                   buflen,
                                   found_node ? nodepool : revpool));
        }
      else if (old_v1_with_cl)
        {
          /* An old-v1 block with a Content-length might have a text block.
             If the property block did not consume all the bytes of the
             Content-length, then it clearly does have a text block.
             If not, then we must deduce whether we have an *empty* text
             block or an *absent* text block.  The rules are:
             - "Node-kind: file" blocks have an empty (i.e. present, but
               zero-length) text block, since they represent a file
               modification.  Note that file-copied-text-unmodified blocks
               have no Content-length - even if they should have contained
               a modified property block, the pre-0.14 dumper forgets to
               dump the modified properties.
             - If it is not a file node, then it is a revision or directory,
               and so has an absent text block.
          */
          const char *node_kind;
          svn_filesize_t cl_value = svn__atoui64(content_length)
                                    - actual_prop_length;

          if (cl_value ||
              ((node_kind = svn_hash_gets(headers,
                                          SVN_REPOS_DUMPFILE_NODE_KIND))
               && strcmp(node_kind, "file") == 0)
             )
            SVN_ERR(parse_text_block(stream,
                                     cl_value,
                                     FALSE,
                                     parse_fns,
                                     found_node ? node_baton : rev_baton,
                                     buffer,
                                     buflen,
                                     found_node ? nodepool : revpool));
        }

      /* if we have a content-length header, did we read all of it?
         in case of an old v1, we *always* read all of it, because
         text-content-length == content-length - prop-content-length
      */
      if (content_length && ! old_v1_with_cl)
        {
          apr_size_t rlen, num_to_read;
          svn_filesize_t remaining =
            svn__atoui64(content_length) -
            (prop_cl ? svn__atoui64(prop_cl) : 0) -
            (text_cl ? svn__atoui64(text_cl) : 0);


          if (remaining < 0)
            return svn_error_create(SVN_ERR_STREAM_MALFORMED_DATA, NULL,
                                    _("Sum of subblock sizes larger than "
                                      "total block content length"));

          /* Consume remaining bytes in this content block */
          while (remaining > 0)
            {
              if (remaining >= (svn_filesize_t)buflen)
                rlen = buflen;
              else
                rlen = (apr_size_t) remaining;

              num_to_read = rlen;
              SVN_ERR(svn_stream_read_full(stream, buffer, &rlen));
              remaining -= rlen;
              if (rlen != num_to_read)
                return stream_ran_dry();
            }
        }

      /* If we just finished processing a node record, we need to
         close the node record and clear the per-node subpool. */
      if (found_node)
        {
          SVN_ERR(parse_fns->close_node(node_baton));
          svn_pool_clear(nodepool);
        }

      /*** End of processing for one record. ***/

    } /* end of stream */

  /* Close out whatever revision we're in. */
  if (rev_baton != NULL)
    SVN_ERR(parse_fns->close_revision(rev_baton));

  svn_pool_destroy(linepool);
  svn_pool_destroy(revpool);
  svn_pool_destroy(nodepool);
  return SVN_NO_ERROR;
}
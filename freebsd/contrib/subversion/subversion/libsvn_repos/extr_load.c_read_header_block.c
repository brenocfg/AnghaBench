#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* data; size_t len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  size_t apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_STREAM_MALFORMED_DATA ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stream_ran_dry () ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  svn_stream_readline (int /*<<< orphan*/ *,TYPE_1__**,char*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_stringbuf_isempty (TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
read_header_block(svn_stream_t *stream,
                  svn_stringbuf_t *first_header,
                  apr_hash_t **headers,
                  apr_pool_t *pool)
{
  *headers = apr_hash_make(pool);

  while (1)
    {
      svn_stringbuf_t *header_str;
      const char *name, *value;
      svn_boolean_t eof;
      apr_size_t i = 0;

      if (first_header != NULL)
        {
          header_str = first_header;
          first_header = NULL;  /* so we never visit this block again. */
          eof = FALSE;
        }

      else
        /* Read the next line into a stringbuf. */
        SVN_ERR(svn_stream_readline(stream, &header_str, "\n", &eof, pool));

      if (svn_stringbuf_isempty(header_str))
        break;    /* end of header block */
      else if (eof)
        return stream_ran_dry();

      /* Find the next colon in the stringbuf. */
      while (header_str->data[i] != ':')
        {
          if (header_str->data[i] == '\0')
            return svn_error_createf(SVN_ERR_STREAM_MALFORMED_DATA, NULL,
                                     _("Dump stream contains a malformed "
                                       "header (with no ':') at '%.20s'"),
                                     header_str->data);
          i++;
        }
      /* Create a 'name' string and point to it. */
      header_str->data[i] = '\0';
      name = header_str->data;

      /* Skip over the NULL byte and the space following it.  */
      i += 2;
      if (i > header_str->len)
        return svn_error_createf(SVN_ERR_STREAM_MALFORMED_DATA, NULL,
                                 _("Dump stream contains a malformed "
                                   "header (with no value) at '%.20s'"),
                                 header_str->data);

      /* Point to the 'value' string. */
      value = header_str->data + i;

      /* Store name/value in hash. */
      svn_hash_sets(*headers, name, value);
    }

  return SVN_NO_ERROR;
}
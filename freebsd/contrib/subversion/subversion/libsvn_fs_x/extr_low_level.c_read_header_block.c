#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t len; char* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  size_t apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,char const*,size_t,char const*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * svn_hash__make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_readline (int /*<<< orphan*/ *,TYPE_1__**,char*,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_header_block(apr_hash_t **headers,
                  svn_stream_t *stream,
                  apr_pool_t *result_pool)
{
  *headers = svn_hash__make(result_pool);

  while (1)
    {
      svn_stringbuf_t *header_str;
      const char *name, *value;
      apr_size_t i = 0;
      apr_size_t name_len;
      svn_boolean_t eof;

      SVN_ERR(svn_stream_readline(stream, &header_str, "\n", &eof,
                                  result_pool));

      if (eof || header_str->len == 0)
        break; /* end of header block */

      while (header_str->data[i] != ':')
        {
          if (header_str->data[i] == '\0')
            return svn_error_createf(SVN_ERR_FS_CORRUPT, NULL,
                                     _("Found malformed header '%s' in "
                                       "revision file"),
                                     header_str->data);
          i++;
        }

      /* Create a 'name' string and point to it. */
      header_str->data[i] = '\0';
      name = header_str->data;
      name_len = i;

      /* Check if we have enough data to parse. */
      if (i + 2 > header_str->len)
        {
          /* Restore the original line for the error. */
          header_str->data[i] = ':';
          return svn_error_createf(SVN_ERR_FS_CORRUPT, NULL,
                                   _("Found malformed header '%s' in "
                                     "revision file"),
                                   header_str->data);
        }

      /* Skip over the NULL byte and the space following it. */
      i += 2;

      value = header_str->data + i;

      /* header_str is safely in our pool, so we can use bits of it as
         key and value. */
      apr_hash_set(*headers, name, name_len, value);
    }

  return SVN_NO_ERROR;
}
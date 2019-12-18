#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stream_translated (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_stringbuf (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
translate_cstring(const char **dst,
                  svn_boolean_t *translated_eol,
                  const char *src,
                  const char *eol_str,
                  svn_boolean_t repair,
                  apr_hash_t *keywords,
                  svn_boolean_t expand,
                  apr_pool_t *pool)
{
  svn_stringbuf_t *dst_stringbuf;
  svn_stream_t *dst_stream;
  apr_size_t len = strlen(src);

  /* The easy way out:  no translation needed, just copy. */
  if (! (eol_str || (keywords && (apr_hash_count(keywords) > 0))))
    {
      *dst = apr_pstrmemdup(pool, src, len);
      return SVN_NO_ERROR;
    }

  /* Create a stringbuf and wrapper stream to hold the output. */
  dst_stringbuf = svn_stringbuf_create_empty(pool);
  dst_stream = svn_stream_from_stringbuf(dst_stringbuf, pool);

  if (translated_eol)
    *translated_eol = FALSE;

  /* Another wrapper to translate the content. */
  dst_stream = stream_translated(dst_stream, eol_str, translated_eol, repair,
                                 keywords, expand, pool);

  /* Jam the text into the destination stream (to translate it). */
  SVN_ERR(svn_stream_write(dst_stream, src, &len));

  /* Close the destination stream to flush unwritten data. */
  SVN_ERR(svn_stream_close(dst_stream));

  *dst = dst_stringbuf->data;
  return SVN_NO_ERROR;
}
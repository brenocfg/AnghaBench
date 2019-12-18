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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_copy3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_disown (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_subst_stream_translated (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_subst_translate_stream3(svn_stream_t *src_stream,
                            svn_stream_t *dst_stream,
                            const char *eol_str,
                            svn_boolean_t repair,
                            apr_hash_t *keywords,
                            svn_boolean_t expand,
                            apr_pool_t *pool)
{
  /* The docstring requires that *some* translation be requested. */
  SVN_ERR_ASSERT(eol_str || keywords);

  /* We don't want the copy3 to close the provided streams. */
  src_stream = svn_stream_disown(src_stream, pool);
  dst_stream = svn_stream_disown(dst_stream, pool);

  /* Wrap the destination stream with our translation stream. It is more
     efficient than wrapping the source stream. */
  dst_stream = svn_subst_stream_translated(dst_stream, eol_str, repair,
                                           keywords, expand, pool);

  return svn_error_trace(svn_stream_copy3(src_stream, dst_stream,
                                          NULL, NULL, pool));
}
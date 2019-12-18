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
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_diff_mem_string_output_unified3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,char const*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_diff_mem_string_output_unified2(svn_stream_t *output_stream,
                                    svn_diff_t *diff,
                                    svn_boolean_t with_diff_header,
                                    const char *hunk_delimiter,
                                    const char *original_header,
                                    const char *modified_header,
                                    const char *header_encoding,
                                    const svn_string_t *original,
                                    const svn_string_t *modified,
                                    apr_pool_t *pool)
{
  return svn_error_trace(svn_diff_mem_string_output_unified3(output_stream,
                                                             diff,
                                                             with_diff_header,
                                                             hunk_delimiter,
                                                             original_header,
                                                             modified_header,
                                                             header_encoding,
                                                             original,
                                                             modified,
                                                             -1 /* context */,
                                                             /* cancel */
                                                             NULL, NULL,
                                                             pool));
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  original_no_final_eol; int /*<<< orphan*/  modified_no_final_eol; TYPE_1__* patch; int /*<<< orphan*/  original_text_range; int /*<<< orphan*/  modified_text_range; int /*<<< orphan*/  apr_file; } ;
typedef  TYPE_2__ svn_diff_hunk_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {scalar_t__ reverse; } ;

/* Variables and functions */
 int /*<<< orphan*/  hunk_readline_original_or_modified (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ *,char,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_diff_hunk_readline_original_text(svn_diff_hunk_t *hunk,
                                     svn_stringbuf_t **stringbuf,
                                     const char **eol,
                                     svn_boolean_t *eof,
                                     apr_pool_t *result_pool,
                                     apr_pool_t *scratch_pool)
{
  return svn_error_trace(
    hunk_readline_original_or_modified(hunk->apr_file,
                                       hunk->patch->reverse ?
                                         &hunk->modified_text_range :
                                         &hunk->original_text_range,
                                       stringbuf, eol, eof,
                                       hunk->patch->reverse ? '-' : '+',
                                       hunk->patch->reverse
                                          ? hunk->modified_no_final_eol
                                          : hunk->original_no_final_eol,
                                       result_pool, scratch_pool));
}
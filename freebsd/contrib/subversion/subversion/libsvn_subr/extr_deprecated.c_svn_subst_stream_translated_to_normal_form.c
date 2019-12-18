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
typedef  scalar_t__ svn_subst_eol_style_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR_IO_UNKNOWN_EOL ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* SVN_SUBST_NATIVE_EOL_STR ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_subst_eol_style_fixed ; 
 scalar_t__ svn_subst_eol_style_native ; 
 scalar_t__ svn_subst_eol_style_none ; 
 int /*<<< orphan*/ * svn_subst_stream_translated (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_subst_stream_translated_to_normal_form(svn_stream_t **stream,
                                           svn_stream_t *source,
                                           svn_subst_eol_style_t eol_style,
                                           const char *eol_str,
                                           svn_boolean_t always_repair_eols,
                                           apr_hash_t *keywords,
                                           apr_pool_t *pool)
{
  if (eol_style == svn_subst_eol_style_native)
    eol_str = SVN_SUBST_NATIVE_EOL_STR;
  else if (! (eol_style == svn_subst_eol_style_fixed
              || eol_style == svn_subst_eol_style_none))
    return svn_error_create(SVN_ERR_IO_UNKNOWN_EOL, NULL, NULL);

 *stream = svn_subst_stream_translated(source, eol_str,
                                       eol_style == svn_subst_eol_style_fixed
                                       || always_repair_eols,
                                       keywords, FALSE, pool);

 return SVN_NO_ERROR;
}
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
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EOL_STR ; 
 char const* SVN_SUBST_NATIVE_EOL_STR ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_subst_eol_style_fixed ; 
 scalar_t__ svn_subst_eol_style_native ; 
 scalar_t__ svn_subst_eol_style_none ; 

svn_boolean_t
svn_subst_translation_required(svn_subst_eol_style_t style,
                               const char *eol,
                               apr_hash_t *keywords,
                               svn_boolean_t special,
                               svn_boolean_t force_eol_check)
{
  return (special || keywords
          || (style != svn_subst_eol_style_none && force_eol_check)
          || (style == svn_subst_eol_style_native &&
              strcmp(APR_EOL_STR, SVN_SUBST_NATIVE_EOL_STR) != 0)
          || (style == svn_subst_eol_style_fixed &&
              strcmp(APR_EOL_STR, eol) != 0));
}
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
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int SVN_WC_TRANSLATE_FORCE_EOL_REPAIR ; 
 int SVN_WC_TRANSLATE_TO_NF ; 
 int /*<<< orphan*/ * svn_wc_translated_file2 (char const**,char const*,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_translated_file(const char **xlated_p,
                       const char *vfile,
                       svn_wc_adm_access_t *adm_access,
                       svn_boolean_t force_repair,
                       apr_pool_t *pool)
{
  return svn_wc_translated_file2(xlated_p, vfile, vfile, adm_access,
                                 SVN_WC_TRANSLATE_TO_NF
                                 | (force_repair ?
                                    SVN_WC_TRANSLATE_FORCE_EOL_REPAIR : 0),
                                 pool);
}
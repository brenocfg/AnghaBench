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
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_PROP_REVISION_AUTHOR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_DATE ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_LOG ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
svn_compat_log_revprops_out_string(const svn_string_t **author,
                                   const svn_string_t **date,
                                   const svn_string_t **message,
                                   apr_hash_t *revprops)
{
  *author = *date = *message = NULL;
  if (revprops)
    {
      *author = svn_hash_gets(revprops, SVN_PROP_REVISION_AUTHOR);
      *date = svn_hash_gets(revprops, SVN_PROP_REVISION_DATE);
      *message = svn_hash_gets(revprops, SVN_PROP_REVISION_LOG);
    }
}
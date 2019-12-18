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
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ DIFF_REVNUM_NONEXISTENT ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,...) ; 

__attribute__((used)) static const char *
diff_label(const char *path,
           svn_revnum_t revnum,
           apr_pool_t *result_pool)
{
  const char *label;
  if (revnum >= 0)
    label = apr_psprintf(result_pool, _("%s\t(revision %ld)"), path, revnum);
  else if (revnum == DIFF_REVNUM_NONEXISTENT)
    label = apr_psprintf(result_pool, _("%s\t(nonexistent)"), path);
  else /* SVN_INVALID_REVNUM */
    label = apr_psprintf(result_pool, _("%s\t(working copy)"), path);

  return label;
}
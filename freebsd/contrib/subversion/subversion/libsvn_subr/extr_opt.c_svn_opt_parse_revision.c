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
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 char* parse_one_rev (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

int
svn_opt_parse_revision(svn_opt_revision_t *start_revision,
                       svn_opt_revision_t *end_revision,
                       const char *arg,
                       apr_pool_t *pool)
{
  char *left_rev, *right_rev, *end;

  /* Operate on a copy of the argument. */
  left_rev = apr_pstrdup(pool, arg);

  right_rev = parse_one_rev(start_revision, left_rev, pool);
  if (right_rev && *right_rev == ':')
    {
      right_rev++;
      end = parse_one_rev(end_revision, right_rev, pool);
      if (!end || *end != '\0')
        return -1;
    }
  else if (!right_rev || *right_rev != '\0')
    return -1;

  return 0;
}
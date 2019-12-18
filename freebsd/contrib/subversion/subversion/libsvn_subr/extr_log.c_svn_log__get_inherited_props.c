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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const* apr_psprintf (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 char* svn_path_uri_encode (char const*,int /*<<< orphan*/ *) ; 

const char *
svn_log__get_inherited_props(const char *path,
                             svn_revnum_t rev,
                             apr_pool_t *pool)
{
  const char *log_path;

  if (path && path[0] != '\0')
    log_path = svn_path_uri_encode(path, pool);
  else
    log_path = "/";
  return apr_psprintf(pool, "get-inherited-props %s r%ld", log_path, rev);
}
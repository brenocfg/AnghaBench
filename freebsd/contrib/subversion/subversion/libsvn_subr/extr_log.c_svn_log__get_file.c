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
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const* apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  svn_path_uri_encode (char const*,int /*<<< orphan*/ *) ; 

const char *
svn_log__get_file(const char *path, svn_revnum_t rev,
                  svn_boolean_t want_contents, svn_boolean_t want_props,
                  apr_pool_t *pool)
{
  return apr_psprintf(pool, "get-file %s r%ld%s%s",
                      svn_path_uri_encode(path, pool), rev,
                      want_contents ? " text" : "",
                      want_props ? " props" : "");
}
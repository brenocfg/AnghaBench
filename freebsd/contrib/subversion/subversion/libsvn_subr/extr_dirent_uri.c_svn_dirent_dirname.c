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
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char* apr_pstrmemdup (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ dirent_previous_segment (char const*,scalar_t__) ; 
 scalar_t__ dirent_root_length (char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  svn_dirent_is_canonical (char const*,int /*<<< orphan*/ *) ; 

char *
svn_dirent_dirname(const char *dirent, apr_pool_t *pool)
{
  apr_size_t len = strlen(dirent);

  assert(svn_dirent_is_canonical(dirent, pool));

  if (len == dirent_root_length(dirent, len))
    return apr_pstrmemdup(pool, dirent, len);
  else
    return apr_pstrmemdup(pool, dirent, dirent_previous_segment(dirent, len));
}
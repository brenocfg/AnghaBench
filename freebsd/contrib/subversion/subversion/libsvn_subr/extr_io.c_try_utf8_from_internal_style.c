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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * cstring_to_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 char const* svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
try_utf8_from_internal_style(const char *path, apr_pool_t *pool)
{
  svn_error_t *error;
  const char *path_utf8;

  /* Special case. */
  if (path == NULL)
    return "(NULL)";

  /* (try to) convert PATH to UTF-8. If that fails, continue with the plain
   * PATH because it is the best we have. It may actually be UTF-8 already.
   */
  error = cstring_to_utf8(&path_utf8, path, pool);
  if (error)
    {
      /* fallback to best representation we have */

      svn_error_clear(error);
      path_utf8 = path;
    }

  /* Toggle (back-)slashes etc. as necessary.
   */
  return svn_dirent_local_style(path_utf8, pool);
}
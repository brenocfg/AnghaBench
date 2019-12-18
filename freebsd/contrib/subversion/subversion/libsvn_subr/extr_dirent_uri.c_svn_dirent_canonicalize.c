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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 char* canonicalize (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 char canonicalize_to_upper (char const) ; 
 int /*<<< orphan*/  type_dirent ; 

const char *
svn_dirent_canonicalize(const char *dirent, apr_pool_t *pool)
{
  const char *dst = canonicalize(type_dirent, dirent, pool);

#ifdef SVN_USE_DOS_PATHS
  /* Handle a specific case on Windows where path == "X:/". Here we have to
     append the final '/', as svn_path_canonicalize will chop this of. */
  if (((dirent[0] >= 'A' && dirent[0] <= 'Z') ||
        (dirent[0] >= 'a' && dirent[0] <= 'z')) &&
        dirent[1] == ':' && dirent[2] == '/' &&
        dst[3] == '\0')
    {
      char *dst_slash = apr_pcalloc(pool, 4);
      dst_slash[0] = canonicalize_to_upper(dirent[0]);
      dst_slash[1] = ':';
      dst_slash[2] = '/';
      dst_slash[3] = '\0';

      return dst_slash;
    }
#endif /* SVN_USE_DOS_PATHS */

  return dst;
}
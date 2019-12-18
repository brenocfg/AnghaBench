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
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int FALSE ; 
 int relpath_is_canonical (char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_canonicalize (char const*,int /*<<< orphan*/ *) ; 

svn_boolean_t
svn_dirent_is_canonical(const char *dirent, apr_pool_t *scratch_pool)
{
  const char *ptr = dirent;
  if (*ptr == '/')
    {
      ptr++;
#ifdef SVN_USE_DOS_PATHS
      /* Check for UNC paths */
      if (*ptr == '/')
        {
          /* TODO: Scan hostname and sharename and fall back to part code */

          /* ### Fall back to old implementation */
          return (strcmp(dirent, svn_dirent_canonicalize(dirent, scratch_pool))
                  == 0);
        }
#endif /* SVN_USE_DOS_PATHS */
    }
#ifdef SVN_USE_DOS_PATHS
  else if (((*ptr >= 'a' && *ptr <= 'z') || (*ptr >= 'A' && *ptr <= 'Z')) &&
           (ptr[1] == ':'))
    {
      /* The only canonical drive names are "A:"..."Z:", no lower case */
      if (*ptr < 'A' || *ptr > 'Z')
        return FALSE;

      ptr += 2;

      if (*ptr == '/')
        ptr++;
    }
#endif /* SVN_USE_DOS_PATHS */

  return relpath_is_canonical(ptr);
}
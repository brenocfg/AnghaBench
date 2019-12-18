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
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ SVN_PATH_IS_EMPTY (char const*) ; 
 char* apr_palloc (int /*<<< orphan*/ *,int) ; 
 char* apr_pmemdup (int /*<<< orphan*/ *,char const*,int) ; 
 char* apr_pstrndup (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ dirent_is_rooted (char const*) ; 
 int dirent_root_length (char const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 
 scalar_t__ svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_dirent_is_canonical (char const*,int /*<<< orphan*/ *) ; 

char *svn_dirent_join(const char *base,
                      const char *component,
                      apr_pool_t *pool)
{
  apr_size_t blen = strlen(base);
  apr_size_t clen = strlen(component);
  char *dirent;
  int add_separator;

  assert(svn_dirent_is_canonical(base, pool));
  assert(svn_dirent_is_canonical(component, pool));

  /* If the component is absolute, then return it.  */
  if (svn_dirent_is_absolute(component))
    return apr_pmemdup(pool, component, clen + 1);

  /* If either is empty return the other */
  if (SVN_PATH_IS_EMPTY(base))
    return apr_pmemdup(pool, component, clen + 1);
  if (SVN_PATH_IS_EMPTY(component))
    return apr_pmemdup(pool, base, blen + 1);

#ifdef SVN_USE_DOS_PATHS
  if (component[0] == '/')
    {
      /* '/' is drive relative on Windows, not absolute like on Posix */
      if (dirent_is_rooted(base))
        {
          /* Join component without '/' to root-of(base) */
          blen = dirent_root_length(base, blen);
          component++;
          clen--;

          if (blen == 2 && base[1] == ':') /* "C:" case */
            {
              char *root = apr_pmemdup(pool, base, 3);
              root[2] = '/'; /* We don't need the final '\0' */

              base = root;
              blen = 3;
            }

          if (clen == 0)
            return apr_pstrndup(pool, base, blen);
        }
      else
        return apr_pmemdup(pool, component, clen + 1);
    }
  else if (dirent_is_rooted(component))
    return apr_pmemdup(pool, component, clen + 1);
#endif /* SVN_USE_DOS_PATHS */

  /* if last character of base is already a separator, don't add a '/' */
  add_separator = 1;
  if (base[blen - 1] == '/'
#ifdef SVN_USE_DOS_PATHS
       || base[blen - 1] == ':'
#endif
        )
          add_separator = 0;

  /* Construct the new, combined dirent. */
  dirent = apr_palloc(pool, blen + add_separator + clen + 1);
  memcpy(dirent, base, blen);
  if (add_separator)
    dirent[blen] = '/';
  memcpy(dirent + blen + add_separator, component, clen + 1);

  return dirent;
}
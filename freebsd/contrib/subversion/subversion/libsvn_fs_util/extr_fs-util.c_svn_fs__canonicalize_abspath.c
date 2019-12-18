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
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 char* apr_palloc (int /*<<< orphan*/ *,size_t) ; 
 char const* apr_pstrmemdup (int /*<<< orphan*/ *,char const*,size_t) ; 
 scalar_t__ is_canonical_abspath (char const*,size_t) ; 
 size_t strlen (char const*) ; 

const char *
svn_fs__canonicalize_abspath(const char *path, apr_pool_t *pool)
{
  char *newpath;
  size_t path_len;
  size_t path_i = 0, newpath_i = 0;
  svn_boolean_t eating_slashes = FALSE;

  /* No PATH?  No problem. */
  if (! path)
    return NULL;

  /* Empty PATH?  That's just "/". */
  if (! *path)
    return "/";

  /* Non-trivial cases.  Maybe, the path already is canonical after all? */
  path_len = strlen(path);
  if (is_canonical_abspath(path, path_len))
    return apr_pstrmemdup(pool, path, path_len);

  /* Now, the fun begins.  Alloc enough room to hold PATH with an
     added leading '/'. */
  newpath = apr_palloc(pool, path_len + 2);

  /* No leading slash?  Fix that. */
  if (*path != '/')
    {
      newpath[newpath_i++] = '/';
    }

  for (path_i = 0; path_i < path_len; path_i++)
    {
      if (path[path_i] == '/')
        {
          /* The current character is a '/'.  If we are eating up
             extra '/' characters, skip this character.  Else, note
             that we are now eating slashes. */
          if (eating_slashes)
            continue;
          eating_slashes = TRUE;
        }
      else
        {
          /* The current character is NOT a '/'.  If we were eating
             slashes, we need not do that any more. */
          if (eating_slashes)
            eating_slashes = FALSE;
        }

      /* Copy the current character into our new buffer. */
      newpath[newpath_i++] = path[path_i];
    }

  /* Did we leave a '/' attached to the end of NEWPATH (other than in
     the root directory case)? */
  if ((newpath[newpath_i - 1] == '/') && (newpath_i > 1))
    newpath[newpath_i - 1] = '\0';
  else
    newpath[newpath_i] = '\0';

  return newpath;
}
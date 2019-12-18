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
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 char* memchr (char const*,char,int) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 

__attribute__((used)) static svn_boolean_t
relpath_is_canonical(const char *relpath)
{
  const char *dot_pos, *ptr = relpath;
  apr_size_t i, len;
  unsigned pattern = 0;

  /* RELPATH is canonical if it has:
   *  - no '.' segments
   *  - no start and closing '/'
   *  - no '//'
   */

  /* invalid beginnings */
  if (*ptr == '/')
    return FALSE;

  if (ptr[0] == '.' && (ptr[1] == '/' || ptr[1] == '\0'))
    return FALSE;

  /* valid special cases */
  len = strlen(ptr);
  if (len < 2)
    return TRUE;

  /* invalid endings */
  if (ptr[len-1] == '/' || (ptr[len-1] == '.' && ptr[len-2] == '/'))
    return FALSE;

  /* '.' are rare. So, search for them globally. There will often be no
   * more than one hit.  Also note that we already checked for invalid
   * starts and endings, i.e. we only need to check for "/./"
   */
  for (dot_pos = memchr(ptr, '.', len);
       dot_pos;
       dot_pos = strchr(dot_pos+1, '.'))
    if (dot_pos > ptr && dot_pos[-1] == '/' && dot_pos[1] == '/')
      return FALSE;

  /* Now validate the rest of the path. */
  for (i = 0; i < len - 1; ++i)
    {
      pattern = ((pattern & 0xff) << 8) + (unsigned char)ptr[i];
      if (pattern == 0x101 * (unsigned char)('/'))
        return FALSE;
    }

  return TRUE;
}
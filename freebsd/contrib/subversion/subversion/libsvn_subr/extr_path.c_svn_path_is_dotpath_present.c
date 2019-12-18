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

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 

svn_boolean_t
svn_path_is_dotpath_present(const char *path)
{
  size_t len;

  /* The empty string does not have a dotpath */
  if (path[0] == '\0')
    return FALSE;

  /* Handle "." or a leading "./" */
  if (path[0] == '.' && (path[1] == '\0' || path[1] == '/'))
    return TRUE;

  /* Paths of length 1 (at this point) have no dotpath present. */
  if (path[1] == '\0')
    return FALSE;

  /* If any segment is "/./", then a dotpath is present. */
  if (strstr(path, "/./") != NULL)
    return TRUE;

  /* Does the path end in "/." ? */
  len = strlen(path);
  return path[len - 2] == '/' && path[len - 1] == '.';
}
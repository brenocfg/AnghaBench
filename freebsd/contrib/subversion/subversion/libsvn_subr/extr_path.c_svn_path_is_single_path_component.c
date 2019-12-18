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

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SVN_PATH_IS_EMPTY (char const*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_canonical (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

svn_boolean_t
svn_path_is_single_path_component(const char *name)
{
  assert(is_canonical(name, strlen(name)));

  /* Can't be empty or `..'  */
  if (SVN_PATH_IS_EMPTY(name)
      || (name[0] == '.' && name[1] == '.' && name[2] == '\0'))
    return FALSE;

  /* Slashes are bad, m'kay... */
  if (strchr(name, '/') != NULL)
    return FALSE;

  /* It is valid.  */
  return TRUE;
}
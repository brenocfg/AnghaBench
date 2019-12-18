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
 char const SVN_CTYPE_ASCII_COLON ; 
 char const SVN_CTYPE_ASCII_DOT ; 
 char const SVN_CTYPE_ASCII_MINUS ; 
 char const SVN_CTYPE_ASCII_UNDERSCORE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ svn_ctype_isalnum (char const) ; 
 scalar_t__ svn_ctype_isalpha (char const) ; 

svn_boolean_t
svn_prop_name_is_valid(const char *prop_name)
{
  const char *p = prop_name;

  /* The characters we allow use identical representations in UTF8
     and ASCII, so we can just test for the appropriate ASCII codes.
     But we can't use standard C character notation ('A', 'B', etc)
     because there's no guarantee that this C environment is using
     ASCII. */

  if (!(svn_ctype_isalpha(*p)
        || *p == SVN_CTYPE_ASCII_COLON
        || *p == SVN_CTYPE_ASCII_UNDERSCORE))
    return FALSE;
  p++;
  for (; *p; p++)
    {
      if (!(svn_ctype_isalnum(*p)
            || *p == SVN_CTYPE_ASCII_MINUS
            || *p == SVN_CTYPE_ASCII_DOT
            || *p == SVN_CTYPE_ASCII_COLON
            || *p == SVN_CTYPE_ASCII_UNDERSCORE))
        return FALSE;
    }
  return TRUE;
}
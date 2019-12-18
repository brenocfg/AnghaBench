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
typedef  size_t apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  svn_ctype_isalnum (char) ; 

__attribute__((used)) static svn_boolean_t
is_hostname(const char *str)
{
  apr_size_t i, len = strlen(str);

  for (i = 0; i < len; i++)
    {
      char c = str[i];

      /* '-' is only legal when not at the start or end of a label */
      if (c == '-')
        {
          if (i + 1 != len)
            {
              if (str[i + 1] == '.')
                return FALSE; /* '-' preceeds a '.' */
            }
          else
            return FALSE; /* '-' is at end of string */

          /* determine the previous character. */
          if (i == 0)
            return FALSE; /* '-' is at start of string */
          else
            if (str[i - 1] == '.')
              return FALSE; /* '-' follows a '.' */
        }
      else if (c != '*' && c != '.' && !svn_ctype_isalnum(c))
        return FALSE; /* some character not allowed */
    }

  return TRUE;
}
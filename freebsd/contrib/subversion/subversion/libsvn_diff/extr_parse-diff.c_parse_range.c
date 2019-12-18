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
typedef  int svn_linenum_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  parse_offset (int*,char*) ; 
 scalar_t__ strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static svn_boolean_t
parse_range(svn_linenum_t *start, svn_linenum_t *length, char *range)
{
  char *comma;

  if (*range == 0)
    return FALSE;

  comma = strstr(range, ",");
  if (comma)
    {
      if (strlen(comma + 1) > 0)
        {
          /* Try to parse the length. */
          if (! parse_offset(length, comma + 1))
            return FALSE;

          /* Snip off the end of the string,
           * so we can comfortably parse the line
           * number the hunk starts at. */
          *comma = '\0';
        }
       else
         /* A comma but no length? */
         return FALSE;
    }
  else
    {
      *length = 1;
    }

  /* Try to parse the line number the hunk starts at. */
  return parse_offset(start, range);
}
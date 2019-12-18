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
typedef  scalar_t__ pcre_uchar ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ const CHAR_BACKSLASH ; 
 scalar_t__ const CHAR_LEFT_SQUARE_BRACKET ; 
 scalar_t__ const CHAR_NULL ; 
 scalar_t__ const CHAR_RIGHT_SQUARE_BRACKET ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL
check_posix_syntax(const pcre_uchar *ptr, const pcre_uchar **endptr)
{
pcre_uchar terminator;          /* Don't combine these lines; the Solaris cc */
terminator = *(++ptr);   /* compiler warns about "non-constant" initializer. */
for (++ptr; *ptr != CHAR_NULL; ptr++)
  {
  if (*ptr == CHAR_BACKSLASH &&
      (ptr[1] == CHAR_RIGHT_SQUARE_BRACKET ||
       ptr[1] == CHAR_BACKSLASH))
    ptr++;
  else if ((*ptr == CHAR_LEFT_SQUARE_BRACKET && ptr[1] == terminator) ||
            *ptr == CHAR_RIGHT_SQUARE_BRACKET) return FALSE;
  else if (*ptr == terminator && ptr[1] == CHAR_RIGHT_SQUARE_BRACKET)
    {
    *endptr = ptr;
    return TRUE;
    }
  }
return FALSE;
}
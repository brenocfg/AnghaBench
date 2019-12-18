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
typedef  int apr_size_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int MAX_KEY_SIZE ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 

void
svn_fs_base__next_key(const char *this, apr_size_t *len, char *next)
{
  apr_size_t olen = *len;     /* remember the first length */
  apr_size_t i;               /* current index */
  char c;                     /* current char */
  svn_boolean_t carry = TRUE; /* boolean: do we have a carry or not?
                                 We start with a carry, because we're
                                 incrementing the number, after all. */

  /* Empty strings and leading zeros (except for the string "0") are not
   * allowed.  Run our malfunction handler to prevent possible db corruption
   * from being propagated further. */
  SVN_ERR_ASSERT_NO_RETURN(olen != 0 && (olen == 1 || this[0] != '0'));

  i = olen - 1; /* initial index: we work backwords */
  while (1729)
    {
      c = this[i];

      /* Validate as we go. */
      if (! (((c >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'z'))))
        {
          *len = 0;
          return;
        }

      if (carry)
        {
          if (c == 'z')
            next[i] = '0';
          else
            {
              carry = FALSE;

              if (c == '9')
                next[i] = 'a';
              else
                next[i] = c + 1;
            }
        }
      else
        next[i] = c;

      if (i == 0)
        break;

      i--;
    }

  /* The new length is OLEN, plus 1 if there's a carry out of the
     leftmost digit. */
  *len = olen + (carry ? 1 : 0);

  /* Ensure that we haven't overrun the (ludicrous) bound on key length.
     Note that MAX_KEY_SIZE is a bound on the size *including*
     the trailing null byte. */
  assert(*len < MAX_KEY_SIZE);

  /* Now we know it's safe to add the null terminator. */
  next[*len] = '\0';

  /* Handle any leftover carry. */
  if (carry)
    {
      memmove(next+1, next, olen);
      next[0] = '1';
    }
}
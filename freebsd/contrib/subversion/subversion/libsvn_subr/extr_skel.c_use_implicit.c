#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int len; scalar_t__* data; } ;
typedef  TYPE_1__ svn_skel_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  size_t apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__* skel_char_type ; 
 scalar_t__ type_name ; 
 scalar_t__ type_paren ; 
 scalar_t__ type_space ; 

__attribute__((used)) static svn_boolean_t
use_implicit(const svn_skel_t *skel)
{
  /* If it's null, or long, we should use explicit-length form.  */
  if (skel->len == 0
      || skel->len >= 100)
    return FALSE;

  /* If it doesn't start with a name character, we must use
     explicit-length form.  */
  if (skel_char_type[(unsigned char) skel->data[0]] != type_name)
    return FALSE;

  /* If it contains any whitespace or parens, then we must use
     explicit-length form.  */
  {
    apr_size_t i;

    for (i = 1; i < skel->len; i++)
      if (skel_char_type[(unsigned char) skel->data[i]] == type_space
          || skel_char_type[(unsigned char) skel->data[i]] == type_paren)
        return FALSE;
  }

  /* If we can't reject it for any of the above reasons, then we can
     use implicit-length form.  */
  return TRUE;
}
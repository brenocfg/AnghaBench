#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* data; int len; int /*<<< orphan*/  is_atom; } ;
typedef  TYPE_1__ svn_skel_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__* skel_char_type ; 
 scalar_t__ type_name ; 
 scalar_t__ type_paren ; 
 scalar_t__ type_space ; 

__attribute__((used)) static svn_skel_t *
implicit_atom(const char *data,
              apr_size_t len,
              apr_pool_t *pool)
{
  const char *start = data;
  const char *end = data + len;
  svn_skel_t *s;

  /* Verify that the atom starts with a name character.  At the
     moment, all callers have checked this already, but it's more
     robust this way.  */
  if (data >= end || skel_char_type[(unsigned char) *data] != type_name)
    return NULL;

  /* Find the end of the string.  */
  while (++data < end
         && skel_char_type[(unsigned char) *data] != type_space
         && skel_char_type[(unsigned char) *data] != type_paren)
    ;

  /* Allocate the skel representing this string.  */
  s = apr_pcalloc(pool, sizeof(*s));
  s->is_atom = TRUE;
  s->data = start;
  s->len = data - start;

  return s;
}